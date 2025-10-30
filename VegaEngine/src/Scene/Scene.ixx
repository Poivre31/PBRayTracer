export module Core:Scene;
import :Layer;
import Entities;
import Render;
import Math;
import std;



namespace Vega {

	struct Transform {
		float4 position{};
		float4 scale{};
		float4 rotation{};
		//int4 parameters{};
	};

	struct Material {
		float4 color{};
	};

	class Object : public Entity {

	public:
		CRigidBody rigidBody;
		CRTPrimitive rtobject;

		void OnUpdate(double timeStep) {
			rigidBody.AddForce(Vec3(0., 0., -.0098 * 0));
			rigidBody.AddForce(-.3 * rigidBody.GetVelocity());
			rigidBody.Update(timeStep);
		}
	};

	struct RTObject {
		Transform transform;
		float4 color;
		int4 data;
	};

	template <typename T>
	static float4 Vec3ToFloat4(Vec3<T> u) {
		return float4{ (float)u.x, (float)u.y, (float)u.z, 0.f };
	}

	export class Scene : public Layer {
	public:

		void BindSSBO(int slotTransform, int slotColor) {
			_transformsBuffer.Bind(slotTransform);
			_colorsBuffer.Bind(slotColor);
		}

		void OnUpdate(double timeStep) override {
			for (auto& body : _entities)
			{
				body.OnUpdate(timeStep);
			}
		}

		void ParseTransforms(Shader* rtShader) {
			_transforms.resize(_entities.size());
			_colors.resize(_entities.size());

			std::array<int, 7> baseIndices{};
			for (size_t i = 1; i < 7; i++)
			{
				baseIndices[i] = baseIndices[i - 1] + _primitiveCounts[i - 1];
			}

			std::array<int, 7> i{};
			for (auto& body : _entities)
			{
				int type = (int)body.rtobject.GetPrimitiveType();
				int index = i[type] + baseIndices[type];
				_transforms[index].position = Vec3ToFloat4(body.rigidBody.GetPosition());
				_transforms[index].scale = Vec3ToFloat4(body.rigidBody.GetScale());
				auto rtp = cart2sph(body.rigidBody.GetRotation());
				_transforms[index].rotation = Vec3ToFloat4(Vec3<double>(rtp.x, rtp.y, 0.));
				_colors[index] = Vec3ToFloat4(body.rtobject.GetColor());
				i[type]++;
			}

			_transformsBuffer.UpdateData(_transforms);
			_colorsBuffer.UpdateData(_colors);
			rtShader->SetInt("count.sphere", _primitiveCounts[PrimitiveType::sphere]);
			rtShader->SetInt("count.cube", _primitiveCounts[PrimitiveType::cube]);
			rtShader->SetInt("count.plane", _primitiveCounts[PrimitiveType::plane]);
			rtShader->SetInt("count.circle", _primitiveCounts[PrimitiveType::circle]);
			rtShader->SetInt("count.cylinder", _primitiveCounts[PrimitiveType::cylinder]);
			rtShader->SetInt("count.cone", _primitiveCounts[PrimitiveType::cone]);
			rtShader->SetInt("count.pyramid", _primitiveCounts[PrimitiveType::pyramid]);
		}

		void AddEntities(const std::vector<Object>& entities) {
			_entities.append_range(entities);

			//if(_transformsBuffer.GetReservedSize() < sizeof(Transform) * _entities.size())
			_transformsBuffer.Reserve(sizeof(RTObject) * _entities.size());
			_colorsBuffer.Reserve(sizeof(RTObject) * _entities.size());
			for (auto& newBody : entities)
			{
				_primitiveCounts[newBody.rtobject.GetPrimitiveType()]++;
			}
		}

		void ClearEntities() {
			_primitiveCounts.fill(0);
			_transforms.clear();
			_colors.clear();
			_entities.clear();
			//_transformsBuffer.Zero();
		}

		static void RandomScene(Scene* scene, size_t nEntities) {
			scene->ClearEntities();
			std::vector<Object> entities;
			entities.reserve(nEntities);
			for (size_t i = 0; i < nEntities; i++)
			{
				Object entity;
				entity.rigidBody.SetPosition(Random::Rand3f(-1.f, 1.f));
				entity.rigidBody.SetScale(Random::Rand3f(0.06f, 0.12f));
				entity.rigidBody.SetRotation(sph2cart(Vec3<double>(1., Random::Randf(0., std::numbers::pi), Random::Randf(0., 2 * std::numbers::pi))));
				entity.rigidBody.SetMass(Random::Randf(0.1, 10.));
				entity.rtobject.SetColor(Random::Rand3f(0.f, 1.f));
				entity.rtobject.SetPrimitiveType(PrimitiveType(Random::Randi(0, 6)));
				entities.push_back(entity);
			}
			scene->AddEntities(entities);
		}

	private:
		std::vector<Object> _entities;
		std::vector<Transform> _transforms;
		std::vector<float4> _colors;
		SSBO<Transform> _transformsBuffer;
		SSBO<float4> _colorsBuffer;
		std::array<int, 7> _primitiveCounts{};
	};

}


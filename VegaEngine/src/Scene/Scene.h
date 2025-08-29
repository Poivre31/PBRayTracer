#pragma once
#include "Camera.h"
#include "Core/Layer.h"
#include "Core/Application.h"
#include "Renderer/Buffer.h"
#include "Entity.h"
#include "Math/Random.h"
#include <iostream>
#include "Renderer/Shader.h"

namespace Vega {

	struct RTObject {
		Transform transform;
		float4 color;
		int4 data;
	};

	template <typename T>
	static float4 Vec3ToFloat4(Vec3<T> u) {
		return float4((float)u.x, (float)u.y, (float)u.z, 0.f);
	}

	class Scene : public Layer {
	public:

		void BindSSBO(GLuint slot) {
			_transformsBuffer.Bind(slot);
		}

		virtual void OnPhysicsUpdate(double timeStep) {
			for (auto& body : _entities)
			{
				body.Update(timeStep);
			}
		}

		void ParseTransforms(Shader* rtShader) {

			int baseIndices[7]{};
			for (int i = 1; i < 7; i++)
			{
				baseIndices[i] = baseIndices[i - 1] + _primitiveCounts[i - 1];
			}

			int i[7]{};
			for (auto& body : _entities)
			{
				int index = i[body.GetPrimitiveType()] + baseIndices[body.GetPrimitiveType()];
				_transforms[index].transform.position = Vec3ToFloat4(body.GetPosition());
				_transforms[index].transform.scale = Vec3ToFloat4(body.GetScale());
				_transforms[index].transform.rotation = Vec3ToFloat4(body.GetOrientation());
				_transforms[index].color = Vec3ToFloat4(body.GetColor());
				_transforms[index].data = int4(body.GetPrimitiveType(), 0, 0, 0);
				i[body.GetPrimitiveType()]++;
			}

			_transformsBuffer.UpdateData(_transforms, _entities.size());
			rtShader->SetInt("count.sphere", _primitiveCounts[PrimitiveType::sphere]);
			rtShader->SetInt("count.cube", _primitiveCounts[PrimitiveType::cube]);
			rtShader->SetInt("count.plane", _primitiveCounts[PrimitiveType::plane]);
			rtShader->SetInt("count.circle", _primitiveCounts[PrimitiveType::circle]);
			rtShader->SetInt("count.cylinder", _primitiveCounts[PrimitiveType::cylinder]);
			rtShader->SetInt("count.cone", _primitiveCounts[PrimitiveType::cone]);
			rtShader->SetInt("count.pyramid", _primitiveCounts[PrimitiveType::pyramid]);
		}

		void SetCamera(Camera& camera) {
			_camera = &camera;
		}

		void AddEntities(const std::vector<Entity>& entities) {
			if (entities.size() + _entities.size() > 4096) {
				Log::error("Trying to add more objects than the limit set at 4096");
				return;
			}
			_entities.append_range(entities);
			
			//if(_transformsBuffer.GetReservedSize() < sizeof(Transform) * _entities.size())
			_transformsBuffer.Reserve(sizeof(RTObject) * _entities.size());

			for (auto& newBody : entities)
			{
				_primitiveCounts[newBody.GetPrimitiveType()]++;
			}
		}

		void ClearEntities() {
			std::memset(_primitiveCounts, 0, 7);
			std::memset(_transforms, 0, 4096);
			_entities.clear();
			//_transformsBuffer.Zero();
		}

		static void RandomScene(Scene* scene, size_t nEntities) {
			scene->ClearEntities();
			std::vector<Entity> entities;
			entities.reserve(nEntities);
			for (size_t i = 0; i < nEntities; i++)
			{
				Entity entity;
				entity.SetPosition(Random::RandVec3d(-1., 1.));
				entity.SetScale(Random::RandVec3d(0.01, 0.04));
				entity.SetColor(Random::RandVec3f(0., 1.));
				entity.SetPrimitiveType(PrimitiveType(Random::RandInt(0,7)));
				entities.push_back(entity);
			}
			scene->AddEntities(entities);
		}

	private:
		Camera* _camera = nullptr;
		std::vector<Entity> _entities;
		RTObject _transforms[4096]{};
		SSBO _transformsBuffer;
		int _primitiveCounts[7];
	};

}


export module Entities:Collection;
import :Components.RigidBody;
import :Entity;
import Utility;
import Math;
import std;

using namespace Vega::Math;

export namespace Vega {

	template<std::derived_from<Entity> T>
	class Collection {
	public:

		Collection() = default;

		Collection(std::vector<T>& entities) : _entities(entities) {};

		~Collection() {
			Clear();
		}

		std::vector<T>& Data() {
			return _entities;
		}

		size_t Size() {
			return _entities.size();
		}

		void Add(T& entity) {
			_entities.push_back(entity);
		}

		void Add(std::vector<T>& entities) {
			_entities.insert(_entities.end(), entities.begin(), entities.end());
		}

		void RemoveEntity(size_t ID) {
			for (auto entity : _entities)
			{
				if (entity.GetID() == ID) {
					Log.error("Entity deletion not yet implemented");
				}
			}
		}

		void Clear() {
			for (auto entity : _entities)
			{
				entity.OnDestroy();
			}
			_entities.clear();
		}

		void Random(size_t size) {
			Clear();
			_entities.reserve(size);
			for (size_t i = 0; i < size; i++)
			{
				auto e = RandomEntity<T>();
				e.OnCreate();
				_entities.push_back(e);
			}
		}

		void Update(double deltaTime) {
			for (int i = 0; i < _entities.size(); i++)
			{
				_entities[i].OnUpdate(deltaTime);
			}
		}


	private:
		std::vector<T> _entities;
	};

}
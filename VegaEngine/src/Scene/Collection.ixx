export module Entities:Collection;
import :Components.RigidBody;
import :Entity;
import Utility;
import Math;

using namespace Vega::Math;

export namespace Vega {

	template<std::derived_from<Entity> T>
	class Collection {
	public:

		Collection() = default;

		Collection(std::vector<T>& entities) : _entities(entities) {};

		std::vector<T>& Data() {
			return _entities;
		}

		size_t Size() {
			return _entities.size();
		}

		void AddEntity(T& entity) {
			_entities.push_back(entity);
		}

		void AddEntities(std::vector<T>& entities) {
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

		void ClearEntities() {
			for (auto entity : _entities)
			{
				entity.OnDestroy();
			}
			_entities.clear();
		}

		void RandomCollection(size_t size) {
			ClearEntities();
			_entities.reserve(size);
			for (size_t i = 0; i < size; i++)
			{
				_entities.push_back(RandomEntity<T>());
			}
		}

		void UpdateCollection(double deltaTime) {
			for (int i = 0; i < _entities.size(); i++)
			{
				_entities[i].OnPhysicsUpdate(deltaTime);
				_entities[i].OnUpdate();
			}
		}


	private:
		std::vector<T> _entities;
	};

}
#pragma once

#include <map>
#include "ecsComponent.h"
#include "ecsSystem.h"

namespace ecs
{
class ECS
{
public:
  ECS(){}
  ~ECS();

  //Remove the copy and assignment operator.
  ECS(const ECS&) = delete;
  ECS& operator=(const ECS&) = delete;

  //Entity methods
  EntityHandle makeEntity(BaseECSComponent* components, const std::uint32_t* componentIDs, std::size_t numComponents);
  void removeEntity(EntityHandle handle);

  //Components methods
  template<typename Component>
  inline void addComponent(EntityHandle handle, Component* component)
  {
    addComponentInternal(handleToEntity(handle), Component::ID, component);
  }

  template<typename Component>
  void removeComponent(EntityHandle handle);

  template<typename Component>
  void getComponent(EntityHandle handle);

  //System methods
  inline void addSystem(BaseECSSystem& system)
  {
    m_systems.push_back(&system);
  }
  void updateSystems(float delta);
  void removeSystem(BaseECSSystem& system);

private:
  //Our base system vector.
  std::vector<BaseECSSystem*> m_systems;

  //A component map. The pair is : component ID with a list of components.
  using ComponentMap = std::map<std::uint32_t, std::vector<std::uint8_t>>;
  ComponentMap m_components;

  using EntitiesVectorMemberData = std::pair<std::uint32_t, std::vector<std::pair<std::uint32_t, std::uint32_t>>>;
  using EntitiesVector = std::vector<EntitiesVectorMemberData* >;

  EntitiesVector m_entities;

  inline EntitiesVectorMemberData* handleToRawType(EntityHandle handle)
  {
    return (EntitiesVectorMemberData*)handle;
  }

  inline std::uint32_t handleToEntityIndex(EntityHandle handle)
  {
    return handleToRawType(handle)->first;
  }

  inline std::vector<std::pair<std::uint32_t, std::uint32_t>>& handleToEntity(EntityHandle handle)
  {
    return handleToRawType(handle)->second;
  }

  void deleteComponent(std::uint32_t componentID, std::uint32_t index);
  void addComponentInternal(std::vector<std::pair<std::uint32_t, std::uint32_t>>& entity, std::uint32_t componentID, BaseECSComponent* component);
};
}

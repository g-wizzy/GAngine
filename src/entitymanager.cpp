#include "entitymanager.h"
#include "components.h"

using namespace component;

EntityManager&
EntityManager::get_instance()
{
    static EntityManager instance;

    return instance;
}

void
EntityManager::begin_new()
{
    current++;
}

Component*
EntityManager::add_component(Type const& type)
{
    switch (type)
    {
    case speed:
        return new Speed(current);

    case color:
        return new Color(current);

    case transform:
        return new Transform(current);

    default:
        return nullptr;
    }
}

Entity&
EntityManager::end_new()
{
    return current;
}
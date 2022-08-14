//
// Created by fmend on 7/4/2022.
//

#include "PhysicsSystem.h"
#include "Components/position.h"
#include "Components/velocity.h"
#include <iostream>

void PhysicsSystem::update(entt::registry &registry) {
    auto view = registry.view<position, velocity>();

    // use a callback
    //view.each([](const auto &pos, auto &vel) { /* ... */ });

    // use an extended callback
    /*view.each([](const auto entity,  auto &pos, auto &vel) { 
        pos.x += vel.dx;
        pos.y += vel.dy;
        std::cout << vel.dx << " " << vel.dy << "\n";
    });*/

    //// use a range-for
    //for(auto [entity, pos, vel]: view.each()) {
    //    
    //}

    //// use forward iterators and get only the components of interest
    //for(auto entity: view) {
    //    auto &vel = view.get<velocity>(entity);
    //    std::cout << vel.dx << " " << vel.dy << "\n";
    //    // ...
    //}
}

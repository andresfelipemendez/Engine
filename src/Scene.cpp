//
// Created by Andres on 28/06/22.
//

#include "Scene.h"
#include <sqlite_orm/sqlite_orm.h>
#include <iostream>

struct User {
    int id;
    std::string name;
    int age;
};

using namespace sqlite_orm;

Scene::Scene() {
    // Create a database connection.
    auto db = make_storage("test.sqlite",
                    make_table("Users",
                        make_column("id", &User::id, autoincrement(), primary_key()),
                        make_column("name", &User::name),
                        make_column("age", &User::age)));

    db.sync_schema();

    User user;
    user.name = "Julian";
    user.age = 35;
    user.id = 1;

    int id = 0;
    try{
        id = db.insert(user);
        std::cout << "Inserted user with id: " << id << std::endl;
    } catch (const std::system_error e) {
        std::cout << e.what() << std::endl;
    }

    try{
        auto users = db.get<User>(id);
        std::cout << users.name << " " << users.age << id << std::endl;
    } catch (const std::system_error e) {
        std::cout << e.what() << std::endl;
    }

}

Scene::~Scene() {

}

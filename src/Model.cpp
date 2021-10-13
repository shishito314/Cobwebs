#include "Model.hpp"
#include "App.hpp"
#include <iostream>

using std::cout, std::endl;

Model::Model(App &app)
: app(app)
{
    cout << "Constructing Model" << endl;
}

void Model::Run()
{}
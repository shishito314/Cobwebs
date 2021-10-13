#pragma once

class App;

class Model
{
public:
    Model(App &app);
    
    void Run();
private:
    App &app;
};
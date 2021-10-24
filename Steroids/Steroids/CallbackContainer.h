#pragma once
class CallbackContainer
{
public:
    virtual void func() = 0;
};

template<class T>
class TypedCallbackContainer : public virtual CallbackContainer
{
private:
    void (T::* callback)();
    T* instance;
public:
    TypedCallbackContainer(void (T::* callback)(), T* instance)
    {
        this->callback = callback;
        this->instance = instance;
    }

    void func()
    {
        (this->instance->*this->callback)();
    }
};

class VoidCallbackContainer : public virtual CallbackContainer
{
private:
    void (*function)();
public:
    VoidCallbackContainer(void (*callback)())
    {
        this->function = callback;
    }

    void func()
    {
        this->function();
    }
};
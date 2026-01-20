export module clonablecomponent;

import <memory>;
import gameobjectcomponent;

// Used to make components clonable, instantiable components inherit from ClonableComponent
// Inheriting from ClonableComponent<Base, Derived> also inherits from Base, component heirarchy is maintained
export template<typename Base, typename Derived> 
class ClonableComponent : public Base {
public:
    using Base::Base;
    // Return heap-allocated copy of the component that inherits this
    std::unique_ptr<Component> clone() const override { return std::make_unique<Derived>(static_cast<const Derived&>(*this)); } 
};

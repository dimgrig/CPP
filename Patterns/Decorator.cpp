#include "Decorator.h"

void DecoratorTest() {
    //need first VeteranUnit ctor
//    {
//        Knight_ptr k(new Knight(10, 5));
//        Unit_ptr o(new Ogre(12, 2));
//        k->charge();
//        std::cout << "Knight hits Ogre: " << k->hit(*o) << std::endl;

//        Unit_ptr t(new Troll(14, 10));
//        std::cout << "Knight hits Troll: " << k->hit(*t) << std::endl;

//        Knight_ptr vk(new VeteranUnit<Knight>(k, 7, 2));
//        std::cout << "Veteran Knight hits Troll: " << vk->hit(*t) << std::endl;

//        //std::unique_ptr<Ogre> ppp(static_cast<Ogre*>(o.release())); // This is the way to cast unique pointers across hierarchy
//        Unit_ptr vo(new VeteranUnit<Ogre>(o, 1, 9));
//        std::cout << "Veteran Knight hits Veteran Ogre: " << vk->hit(*vo) << std::endl;

//        Unit_ptr vvo(new VeteranUnit<VeteranUnit<Ogre>>(vo, 1, 9));
//        std::cout << "Veteran Knight hits Veteran2 Ogre: " << vk->hit(*vvo) << std::endl;

//        vk->charge();
//        std::cout << "Veteran Knight hits Veteran2 Ogre: " << vk->hit(*vvo) << std::endl;

//        {
//            //Unit_ptr k(new Knight(10, 5));
//            //Unit_ptr vk(new VeteranUnit<Ogre>(k, 7, 2));
//        }
//    }
    {
        DebugDecorator<Knight> k(10, 5);
        DebugDecorator<Ogre> o(12, 2);

        k(&Knight::hit, o);
        k(&Knight::charge);

        k.charge();
        std::cout << "Knight hits Ogre: " << k.hit(o) << std::endl;

        Troll t(14, 10);
        std::cout << "Knight hits Troll: " << k.hit(t) << std::endl;

        DebugDecorator<VeteranUnit<Knight>> vk(std::move(k), 7, 2);
        std::cout << "Veteran Knight hits Troll: " << vk.hit(t) << std::endl;

        DebugDecorator<VeteranUnit<Ogre>> vo(std::move(o), 1, 9);
        std::cout << "Veteran Knight hits Veteran Ogre: " << vk.hit(vo) << std::endl;

        DebugDecorator<VeteranUnit<VeteranUnit<Ogre>>> vvo(std::move(vo), 1, 9);
        std::cout << "Veteran Knight hits Veteran2 Ogre: " << vk.hit(vvo) << std::endl;

        vk.charge();
        std::cout << "Veteran Knight hits Veteran2 Ogre: " << vk.hit(vvo) << std::endl;
    }
}

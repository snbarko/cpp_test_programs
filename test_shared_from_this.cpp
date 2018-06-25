#include <iostream>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

class abc;

class abc: public boost::enable_shared_from_this<abc>
{
public:
    abc()
    {
        std::cout << "abc constructor" << std::endl;
    }

    ~abc()
    {
        std::cout << "abc destructor" << std::endl;
        // boost::shared_ptr <abc> x(shared_from_this());
    }

    int data;
};

// int main1()
// {
//     boost::weak_ptr<abc> x;
//     {
//         boost::shared_ptr<abc> y;
//         {
//             boost::shared_ptr<abc> z(new abc);
//             z->data = 55;
//             std::cout << "sharedptr count " << z.use_count() << " valid: " << z.get() << " value: " << z->data << std::endl;
//             std::cout << "x weakptr count " << x.use_count() << std::endl;
//             x = z;
//             std::cout << "x weakptr count " << x.use_count() << std::endl;
//             std::cout << "sharedptr count " << z.use_count() << " valid: " << z.get() << " value: " << z->data << std::endl;

//             {
//                 boost::shared_ptr<abc> y(z);
//                 std::cout << "sharedptr count " << z.use_count() << " valid: " << z.get() << " value: " << z->data << std::endl;
//             }

//             std::cout << "sharedptr count " << z.use_count() << " valid: " << z.get() << " value: " << z->data << std::endl;
//             y = z;
//             std::cout << "sharedptr count " << z.use_count() << " valid: " << z.get() << " value: " << z->data << std::endl;
//             std::cout << "y sharedptr count " << y.use_count() << " valid: " << y.get() << " value: " << y->data << std::endl;
//             std::cout << "x weakptr count " << x.use_count() << std::endl;
//             {
//                 boost::shared_ptr<abc> v;
//                 if (v = x.lock()) {
//                     std::cout << "My print " << v->data << " " << v.use_count() << std::endl;
//                 } else {
//                     std::cout << "shared ptr is not valid" << std::endl;
//                 }
//                 std::cout << "y sharedptr count " << y.use_count() << std::endl;// << " valid: " << y.get() << " value: " << y->data << std::endl;
//             }
//             std::cout << "y sharedptr count " << y.use_count() << std::endl;// << " valid: " << y.get() << " value: " << y->data << std::endl;
//             y.reset();
//             std::cout << "sharedptr count " << z.use_count() << " valid: " << z.get() << " value: " << z->data << std::endl;
//             std::cout << "y sharedptr count " << y.use_count() << std::endl;// << " valid: " << y.get() << " value: " << y->data << std::endl;
//             std::cout << "x weakptr count " << x.use_count() << " valid? " << (x.lock()? "y":"n") << std::endl;
//         }
//         std::cout << "y sharedptr count " << y.use_count() << std::endl;// << " valid: " << y.get() << " value: " << y->data << std::endl;
//     }
//     std::cout << "x weakptr count " << x.use_count() << " valid? " << (x.lock()? "y":"n") << std::endl;
//     // std::cout << "x weakptr count " << x.use_count() << std::endl;
//     boost::shared_ptr<abc> w;
//     if (w = x.lock()) {
//         std::cout << w->data << std::endl;
//     } else {
//         std::cout << "shared ptr is not valid" << std::endl;
//     }
//     return 0;
// }

int main()
{
    abc *x = new abc();
    boost::shared_ptr<abc> z(x);
    std::cout << "SNB " << z.use_count() << std::endl;
    return 0;
}

#include <iostream>
#include <string>
struct Tracer{
   explicit Tracer(std::string name="")
   :name{name}{
       std::cout << "Tracer created: " << name << std::endl;
   }
   ~Tracer(){
       std::cout << "Tracer destroyed: " << name << std::endl;
   }
   Tracer(Tracer const& other)
   :name{other.name+" copy"}{
       std::cout << "Tracer copied: " << name << std::endl;
   }
   void show() const {
       std::cout << "Tracer: " << name << std::endl;
}
   std::string name;
};
int main(){
   Tracer m{"main"};
   {
       Tracer inner{"inner"}; Tracer otherinner{inner};
       inner.show();
   }
   Tracer{"temp"};
m.show(); }

#include <iostream>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

class Circle;

class Drawable 
{
public: // should be private

    struct concept_t // functions listed here as "exec_<function_name>"
    {
        virtual ~concept_t() = default;
        virtual void exec_draw() const = 0; // abstract class
    };
    
    template <typename T>
    struct model_t : public concept_t 
    {
        static_assert(!std::is_const_v<T>, "Shouldn't be const here");

        model_t() = default;
        virtual ~model_t() = default;

        model_t(const T& v) : m_data(v) {}
        model_t(T&& v) : m_data(std::move(v)) {}
        
        void exec_draw() const override { f_draw(m_data); }
        
        T m_data;
    };
    
   
public:
   std::unique_ptr<concept_t> m_impl;

   Drawable() = default;
   Drawable(const Drawable&) = delete;
   Drawable(Drawable&&) = default;
   
   Drawable& operator=(const Drawable&) = delete;
   Drawable& operator=(Drawable&&) = default;

   template <typename T>
   Drawable(T&& impl)
     : m_impl(new model_t<std::decay_t<T>>(std::forward<T>(impl))) {}

   template <typename T>
   Drawable& operator=(T&& impl) 
   {
      m_impl.reset(new model_t<std::decay_t<T>>(std::forward<T>(impl)));
      return *this;
   }
   
   void draw() const { m_impl->exec_draw(); }
   
   template<typename T = Circle>
   T derived();
};

struct Rectangle 
{
    int h = 0;
    int w = 0;
    Rectangle(int h, int w): h(h), w(w) {}
};

struct Circle 
{
    int diameter;
    Circle(int d): diameter(d) {}
    void circle_diameter(){ cout << "diameter = " << diameter << endl;}
};

struct Sprite 
{
    const std::string path;
    Sprite(const std::string& path):path(path) {}
};

void f_draw(const Rectangle& rectangle) {
    std::cout << "Rectangle Dim = [" << rectangle.h << "," << rectangle.w << "]" << std::endl;
}
void f_draw(const Circle& circle) 
{
    std::cout << "Circle Diameter = " << circle.diameter <<  std::endl;
}
void f_draw(const Sprite& sprite) 
{
    std::cout << "Drawing sprite = " << sprite.path << std::endl;
}

template<typename T>
T Drawable::derived(){
    return dynamic_cast<Drawable::model_t<T>*>(&*this->m_impl.get())->m_data;
}

int main() {
    std::vector<Drawable> objects;
    objects.push_back(Rectangle(12, 42)); // First Object Added
    objects.push_back(Circle(10));
    objects.push_back(Sprite("assets/monster.png"));

    for(const Drawable& obj : objects)
        obj.draw(); // Call the polymorphic method


    Drawable* circle = &objects[1];
    // Next we use the long way and the short way of calling function that are NOT polymorphic
    dynamic_cast<Drawable::model_t<Circle>*>(&*circle->m_impl.get())->m_data.circle_diameter(); // Long Way
    circle->derived<>().circle_diameter(); // Short Way

    return 0;
}

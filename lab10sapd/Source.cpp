#include <iostream>
#include <vector>
#include <string>

// Структура для хранения рецепта
struct Recipe 
{
    std::string name;         // название рецепта
    std::string ingredients;  // ингредиенты
    std::string instructions; // инструкции
};

class Cookbook 
{
private:
    std::vector<Recipe> recipes; // вектор для хранения рецептов
    int size;                     // размер книги рецептов
    float loadFactor;             // коэффициент заполнения

    // Функция хеширования
    int hash(std::string key) 
    {
        int sum = 0;
        for (char c : key)
            sum += c;
        
        int square = sum * sum;
        std::string strSquare = std::to_string(square);
        int mid = strSquare.size() / 2;
        std::string strHash = strSquare.substr(mid - 1, 2);
        return std::stoi(strHash) % size;
    }

    // Функция рехеширования
    void rehash() 
    {
        int oldSize = size;
        size *= 2; // увеличиваем размер таблицы в два раза
        std::vector<Recipe> oldRecipes = recipes;
        recipes.clear();
        recipes.resize(size);
        for (int i = 0; i < oldSize; i++) 
            if (!oldRecipes[i].name.empty()) 
                addRecipe(oldRecipes[i]);
            
        
    }

public:
    // Конструктор
    Cookbook(int size, float loadFactor) : size(size), loadFactor(loadFactor) 
    {
        recipes.resize(size);
    }

    // Функция для добавления рецепта
    void addRecipe(Recipe recipe) 
    {
        if ((float)size / recipes.size() > loadFactor) 
            rehash(); // вызываем рехеширование, если таблица заполнена более чем на заданный коэффициент
        
        int index = hash(recipe.name);
        int i = 0;
        while (!recipes[(index + i * i) % size].name.empty() && i < size) 
            i++;
        
        recipes[(index + i * i) % size] = recipe;
    }

    // Функция для получения рецепта
    Recipe getRecipe(std::string name) 
    {
        int index = hash(name);
        int i = 0;
        while (recipes[(index + i * i) % size].name != name && i < size) 
            i++;
        
        return recipes[(index + i * i) % size];
    }
};

int main() 
{
    system("chcp 1251");

    Cookbook cookbook(10, 0.75); // создание книги рецептов с коэффициентом заполнения 0.75

    // добавление рецептов
    Recipe recipe1 = { "Блины", "Мука, Яйца, Молоко", "Смешать ингредиенты и готовить на сковороде" };
    Recipe recipe2 = { "Яичница", "Яйца, Соль, Масло", "Взбить яйца, добавить соль и готовить на масле" };
    Recipe recipe3 = { "Тост с сыром", "Хлеб, Сыр, Масло", "Намазать хлеб маслом, добавить сыр и гриль" };
    cookbook.addRecipe(recipe1);
    cookbook.addRecipe(recipe2);
    cookbook.addRecipe(recipe3);

    // получение рецепта
    Recipe retrievedRecipe = cookbook.getRecipe("Т");
    std::cout << "Рецепт: " << retrievedRecipe.name << "\nИнгредиенты: " << retrievedRecipe.ingredients << "\nИнструкции: " << retrievedRecipe.instructions << std::endl;
    
    return 0;
}

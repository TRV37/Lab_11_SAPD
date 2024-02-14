#include <iostream>
#include <vector>
#include <string>

// ��������� ��� �������� �������
struct Recipe 
{
    std::string name;         // �������� �������
    std::string ingredients;  // �����������
    std::string instructions; // ����������
};

class Cookbook 
{
private:
    std::vector<Recipe> recipes; // ������ ��� �������� ��������
    int size;                     // ������ ����� ��������
    float loadFactor;             // ����������� ����������

    // ������� �����������
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

    // ������� �������������
    void rehash() 
    {
        int oldSize = size;
        size *= 2; // ����������� ������ ������� � ��� ����
        std::vector<Recipe> oldRecipes = recipes;
        recipes.clear();
        recipes.resize(size);
        for (int i = 0; i < oldSize; i++) 
            if (!oldRecipes[i].name.empty()) 
                addRecipe(oldRecipes[i]);
            
        
    }

public:
    // �����������
    Cookbook(int size, float loadFactor) : size(size), loadFactor(loadFactor) 
    {
        recipes.resize(size);
    }

    // ������� ��� ���������� �������
    void addRecipe(Recipe recipe) 
    {
        if ((float)size / recipes.size() > loadFactor) 
            rehash(); // �������� �������������, ���� ������� ��������� ����� ��� �� �������� �����������
        
        int index = hash(recipe.name);
        int i = 0;
        while (!recipes[(index + i * i) % size].name.empty() && i < size) 
            i++;
        
        recipes[(index + i * i) % size] = recipe;
    }

    // ������� ��� ��������� �������
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

    Cookbook cookbook(10, 0.75); // �������� ����� �������� � ������������� ���������� 0.75

    // ���������� ��������
    Recipe recipe1 = { "�����", "����, ����, ������", "������� ����������� � �������� �� ���������" };
    Recipe recipe2 = { "�������", "����, ����, �����", "������ ����, �������� ���� � �������� �� �����" };
    Recipe recipe3 = { "���� � �����", "����, ���, �����", "�������� ���� ������, �������� ��� � �����" };
    cookbook.addRecipe(recipe1);
    cookbook.addRecipe(recipe2);
    cookbook.addRecipe(recipe3);

    // ��������� �������
    Recipe retrievedRecipe = cookbook.getRecipe("�");
    std::cout << "������: " << retrievedRecipe.name << "\n�����������: " << retrievedRecipe.ingredients << "\n����������: " << retrievedRecipe.instructions << std::endl;
    
    return 0;
}

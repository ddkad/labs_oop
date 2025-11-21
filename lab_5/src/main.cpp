#include <iostream>
#include <string>

#include "../include/dynamic_memory_resource.hpp"
#include "../include/queue.hpp"

struct Employee {
  int id;
  std::string name;
  std::string position;

  Employee(int id, std::string name, std::string position)
      : id(id), name(std::move(name)), position(std::move(position)) {}

  friend std::ostream &operator<<(std::ostream &os, const Employee &emp) {
    return os << "Employee{id=" << emp.id << ", name='" << emp.name
              << "', position='" << emp.position << "'}";
  }
};

int main() {
  memory::DynamicMemoryResource custom_resource;
  custom::pmr::Queue<int> int_queue(&custom_resource);

  std::cout << "1. Работа с простыми типами (int):\n";
  for (int i = 1; i <= 5; ++i) {
    int_queue.Push(i * 10);
    std::cout << "Добавлен: " << i * 10 << std::endl;
  }

  std::cout << "\nСодержимое очереди: ";
  for (auto value : int_queue) {
    std::cout << value << " ";
  }
  std::cout << "\nРазмер очереди: " << int_queue.GetSize() << std::endl;

  std::cout << "\nИзвлекаем элементы:\n";
  while (!int_queue.IsEmpty()) {
    std::cout << "Извлечен: " << int_queue.Front() << std::endl;
    int_queue.Pop();
  }

  std::cout << "\n2. Работа со сложными типами (Employee):\n";
  custom::pmr::Queue<Employee> employee_queue(&custom_resource);

  employee_queue.Emplace(1, "Иван Петров", "Разработчик");
  employee_queue.Emplace(2, "Мария Сидорова", "Тестировщик");
  employee_queue.Emplace(3, "Алексей Иванов", "Менеджер");

  std::cout << "Сотрудники в очереди:\n";
  for (const auto &employee : employee_queue) {
    std::cout << " - " << employee << "\n";
  }

  std::cout << "\n3. Демонстрация переиспользования памяти:\n";
  custom::pmr::Queue<std::string> string_queue(&custom_resource);

  for (int i = 0; i < 3; ++i) {
    std::cout << "Цикл " << (i + 1) << ":\n";
    for (int j = 0; j < 3; ++j) {
      string_queue.Push("Элемент_" + std::to_string(j));
    }
    std::cout << "   Добавлено 3 элемента\n";
    while (!string_queue.IsEmpty()) {
      string_queue.Pop();
    }
    std::cout << "   Все элементы удалены (память в пуле)\n";
  }
  return 0;
}
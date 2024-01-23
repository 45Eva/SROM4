#include <iostream>
#include <array>
#include <limits>

const size_t size = 173;
using Element = std::array<bool, size>;
//Мультиплікативна матриця
std::array<Element, size> multiplicativeMatrix;
using Matrix = std::array<Element, size>;

void MultiplicativeMatrix() {
    int p = 2 * size + 1;
    std::array<int, size> array;
    array[0] = 1;

    // Fill the array with the appropriate values
    for (size_t i = 1; i < size; ++i) {
        array[i] = (array[i - 1] * 2) % p;
    }

    // Initialize the multiplicative matrix
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            int two_i = array[i];
            int two_j = array[j];

            // Check the conditions to determine the value for the multiplicative matrix
            if ((two_i + two_j) % p == 1 ||
                (two_i - two_j + p) % p == 1 ||
                ((p - two_i) + two_j) % p == 1 ||
                ((p - two_i) - two_j + p) % p == 1) {
                multiplicativeMatrix[i][j] = true; // 1 in binary
            }
            else {
                multiplicativeMatrix[i][j] = false; // 0 in binary
            }
        }
    }
}

/*void createCustomElement(Element& coefficients, const std::array<size_t, size>& coefArray, size_t coefCount) {
    coefficients.fill(false);

    for (size_t i = 0; i < coefCount; ++i) {
        if (coefArray[i] < size) {
            coefficients[coefArray[i]] = true;
        }
    }
} */

void createCustomElement(Element& coefficients, const std::string& coefString) {
    coefficients.fill(false);

    for (size_t i = 0; i < size && i < coefString.length(); ++i) {
        coefficients[size - i - 1] = (coefString[i] == '1');
    }
}


// Функція для перевертання масиву як того потребує стандарт 
Element Correct_OutPut(const Element& arr) {
    Element reversedArray;

    for (size_t i = 0; i < size; ++i) {
        reversedArray[i] = arr[size - i - 1];
    }

    return reversedArray;
}


void printElement(const Element& coefficients) {
    for (size_t i = 0; i < size; ++i) {
        std::cout << coefficients[i];
    }
    std::cout << std::endl;
}

void toCoefficientArray(const Element& coefficients, std::array<size_t, size>& result, size_t& arraySize) {
    arraySize = 0;
    for (size_t i = 0; i < size && arraySize < size; ++i) {
        if (coefficients[i]) {
            result[arraySize++] = i;
        }
    }
}

void printCoef(const std::array<size_t, size>& result, size_t arraySize) {
    for (size_t i = 0; i < arraySize; ++i) {
        std::cout << result[i] << " ";
    }
    std::cout << std::endl;
}

// Функція для перевірки, чи всі елементи масиву дорівнлюють нулю. (Нейтральние ел. по + )
bool Const_0(Element& field_element) {
    for (bool element : field_element) {
        if (element) {
            return false; // Знайдено елемент, не дорівнює нулю
        }
    }
    return true; // Всі елементи дорівнюють нулю
}

// Функція для перевірки, чи всі елементи масиву дорівнлюють одиниці. (Нейтральние ел. по * ) ?111..11 ?
bool Const_1(Element& field_element) {
    for (bool element : field_element) {
        if (!element) {
            return false; // Знайдено елемент, не дорівнює одиниці
        }
    }
    return true; // Всі елементи дорівнюють одиниці
}

// Функція для додавання двох елементів поля
Element Add(Element& field1, Element& field2) {
    Element result;
    for (size_t i = 0; i < size; ++i) {
        result[i] = field1[i] ^ field2[i]; // XOR для додавання бітів
    }
    return result;
}


// Функція для піднесення до квадрата елемента поля
Element Square(const Element& element) {
    Element result;
    // Циклічний зсув вправо компонентів векторного зображення елемента
    for (size_t i = size - 1; i > 0; i--) {
        result[i - 1] = element[i];
    }
    // Переміщення останнього значення на початок
    result[size - 1] = element[0];
    return result;
}

// Функція для обчислення сліду елемента поля у нормальному базисі
bool Trace(const Element& element) {
    bool trace = false;
    // Обчислення сліду як XOR всіх коефіцієнтів у нормальному базисі
    for (bool value : element) {
        trace ^= value; // XOR
    }
    return trace;
}

// Циклічні зсуви ел.поля 
// Функція зсуву ліворуч
Element Left_Shift(const Element& element, int positions) {
    Element result;
    for (size_t i = 0; i < size; ++i) {
        result[i] = element[(i + positions) % size];
    }
    return result;
}

// Функція зсуву праворуч
Element Right_Shift(const Element& element, int positions) {
    Element result;
    for (size_t i = 0; i < size; ++i) {
        result[i] = element[(i - positions + size) % size];
    }
    return result;
}

// Функція для транспонування матриці
Matrix Transpose(const Matrix& matrix) {
    Matrix transposed;
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            transposed[i][j] = matrix[j][i];
        }
    }
    return transposed;
}

// Функція для множення елементів
Element mirror(const Element& element) {
    Element  result;
    for (int i = 0; i < size; i++) {
        result[size - 1 - i] = element[i];
    }

    return result;
}

Element Multiply(const Element& A, const Element& B)
{
    Element result;

    Element u = mirror(A);
    Element v = mirror(B);
    Element temp;


    for (int i = 0; i < size; ++i) {


        for (int j = 0; j < size; j++) {

            int s = 0;
            for (int k = 0; k < size; k++) {
                s += u[k] * multiplicativeMatrix[j][k];
            }
            temp[j] = s & 1;
        }
        int ss = 0;
        for (int j = 0; j < size; j++) {
            int s = 0;
            for (int k = 0; k < size; k++) {
                s += temp[k] * v[k];
            }
            ss += s & 1;
        }



        u = Left_Shift(u, 1);
        v = Left_Shift(v, 1);

        result[i] = ss & 1;
    }

    result = Right_Shift(Square(result), 1);
    return result;
}

// Функція для піднесення до квадрата елемента поля
Element Square_1(const Element& element) {
    Element result;
    result = Multiply(element, element);
    return result;
}


// Піднесення до степеня ел.поля   ????????
Element Power(const Element& base, const Element& power)
{
    Element result;
    result.fill(true);
    Element temp = base;

    for (int i = size - 1; i > 0; i--) {

        if (power[i] & 1) {
            result = Multiply(result, temp);
        }
        temp = Square(temp);
    }

    return result;
}

// Оберненого ел. за множенням 
/*Element Inverse(const Element& element)
{
    Element beta = element;

    int k = 1;
    std::string m_binary = "10101100";   // m - 1 = 172   10101100

    for (int i = 0; i < 8; ++i)
    {
        Element original_beta = beta;

        for (int j = 0; j < k; ++j)
        {
            beta = Square_1(beta);
        }

        beta = Multiply(beta, original_beta);
        k *= 2;

        if (m_binary[i] == '1')
        {
            Element squared_beta = Square_1(beta);
            beta = Multiply(squared_beta, element);
            ++k;
        }
    }

    beta = Square_1(beta);
    return beta;
} */


int main() {
    // Ініціалізація мультиплікативної матрицці
    MultiplicativeMatrix();

    // Виведення матриці 
   /* for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            std::cout << multiplicativeMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    } */

    // якщо вводиит вручну коефіцієнти
   /* Element A;
    Element B;
    Element C;
    std::array<size_t, size> coefArrayA;
    std::array<size_t, size> coefArrayB;
    std::array<size_t, size> coefArrayC;
    size_t indexA = 0;
    size_t indexB = 0;
    size_t indexC = 0;
    int coef;

    std::cout << "Enter coefficients for element A (empty line to stop '/n'):" << std::endl;
    while (indexA < size && std::cin >> coef) {
        coefArrayA[indexA++] = coef;
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter coefficients for element B (empty line to stop '/n'):" << std::endl;
    while (indexB < size && std::cin >> coef) {
        coefArrayB[indexB++] = coef;
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter coefficients for element C (empty line to stop '/n'):" << std::endl;
    while (indexB < size && std::cin >> coef) {
        coefArrayC[indexC++] = coef;
    }

    // створення ел. поля
    createCustomElement(A, coefArrayA, indexA);
    createCustomElement(B, coefArrayB, indexB);
    createCustomElement(C, coefArrayC, indexC);

    std::cout << "Element A:" << std::endl;
    printElement(A);
    std::cout << "Element B:" << std::endl;
    printElement(B);
    std::cout << "Element C:" << std::endl;
    printElement(C);

    // перетворення ел. поля у коефіцієнти
    std::array<size_t, size> coefArrayResultA;
    size_t arraySizeA;
    toCoefficientArray(A, coefArrayResultA, arraySizeA);

    std::array<size_t, size> coefArrayResultB;
    size_t arraySizeB;
    toCoefficientArray(B, coefArrayResultB, arraySizeB);

    std::array<size_t, size> coefArrayResultC;
    size_t arraySizeC;
    toCoefficientArray(C, coefArrayResultC, arraySizeC);

    std::cout << "Coefficient array for A:" << std::endl;
    printCoef(coefArrayResultA, arraySizeA);
    std::cout << "Coefficient array for B:" << std::endl;
    printCoef(coefArrayResultB, arraySizeB);
    std::cout << "Coefficient array for C:" << std::endl;
    printCoef(coefArrayResultC, arraySizeC); */

    // Захаркодити елементи 

    Element A;
    Element B;
    Element C;
    std::string coefStringA = "10110101011101111110100011011110111101110111100000101000100000001101001111101000001111000000011001110101011100111110100001110111011011010000011011010000000011110010100100110";
    std::string coefStringB = "01101010000100110110101000010011000100010001000010011010011110010000101000001111001011001100100101011011111001000010011010010000100101011000110111010000010111010001111111011";
    std::string coefStringC = "10101001011011000110100111000000111100001111000101100101101001011110011100000001000001101110110100000001000000100111010011101101010110100111111111011000110101001011001110010";

    // створення ел. поля
    createCustomElement(A, coefStringA);
    createCustomElement(B, coefStringB);
    createCustomElement(C, coefStringC);

    //Перевірка функції чи є ел. нулем
    std::cout << "Const 0 for A ? :" << std::endl;
    std::cout << (Const_0(A) ? "True" : "False") << std::endl;

    //Перевірка функції чи є ел. одиницею
    std::cout << "Const 1 for B ? :" << std::endl;
    std::cout << (Const_1(B) ? "True" : "False") << std::endl;

    //Додавання двох елементів поля 
    Element add;
    add = Add(A, B);
    std::cout << "A + B  :" << std::endl;
    printElement(Correct_OutPut(add));

    //Піднесення до квадрату ел. поля 
    Element squared = Square(A);
    std::cout << "Squared element: " << std::endl;
    printElement(Correct_OutPut(squared));

    //Обчислення сліду ел. поля 
    bool traceA = Trace(A);
    std::cout << "Trace of the element A : " << traceA << std::endl;
    bool traceB = Trace(B);
    std::cout << "Trace of the element B: " << traceB << std::endl;
    bool traceC = Trace(C);
    std::cout << "Trace of the element C: " << traceC << std::endl;

    // Зсуви 
   /* // Зсув ліворуч
    Element shiftedLeft = Left_Shift(A, 3);
    // Зсув праворуч
    Element shiftedRight = Right_Shift(A, 2);
    // Виводимо результати зсуву
    for (size_t i = 0; i < size; ++i) {
        std::cout << shiftedLeft[i] << " ";
    }
    std::cout << std::endl;

    for (size_t i = 0; i < size; ++i) {
        std::cout << shiftedRight[i] << " ";
    }
    std::cout << std::endl; */

    // Множення ел. поля 
    Element mul = Multiply(A, B);
    std::cout << "A * B: " << std::endl;
    printElement(mul);

    //Піднесення до степеня  &&&&&&&&&&&&&&&&&&&&
    Element powe = Power(A, C);
    std::cout << "A ^ C  :" << std::endl;
    printElement(powe);


    // Обернений ел. за множенням 
   /* Element verse = Inverse(A);
    std::cout << "A ^ (-1): " << std::endl;
    printElement(verse);
     */

     // Тестування : 
     //(a + b) * c = b*c + c*a
    std::cout << "Testting : (a + b) * c = b*c + c*a " << std::endl;
    Element test1;
    test1 = Multiply(Add(A, B), C);
    std::cout << " (a + b) * c :" << std::endl;
    printElement(test1);
    std::array<size_t, size> coefArrayResult_test1;
    size_t arraySize_test1;
    toCoefficientArray(test1, coefArrayResult_test1, arraySize_test1);

    Element test2;
    Element a = Multiply(B, C);
    Element b = Multiply(C, A);
    test2 = Add(a, b);
    std::cout << " b*c + c*a :" << std::endl;
    printElement(test2);
    std::array<size_t, size> coefArrayResult_test2;
    size_t arraySize_test2;
    toCoefficientArray(test2, coefArrayResult_test2, arraySize_test2);

    std::cout << " (a + b) * c :" << std::endl;
    printCoef(coefArrayResult_test1, arraySize_test1);
    std::cout << " b*c + c*a :" << std::endl;
    printCoef(coefArrayResult_test2, arraySize_test2);

}

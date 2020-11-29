#include <iostream>
#include <ctime>

using namespace std;

int main()
{
    setlocale(0, "");
    srand(time(0));

    short operation;
    cout << "Ручной ввод или случайная генерация?" << endl;
    cout << "1 - Ввести вручную" << endl;
    cout << "2 - Сгенерировать случайным образом" << endl;

    bool ok = false;
    int arr [30];
    int n;

    //Input
    do
    {
        cin >> operation;
        switch (operation)
        {
        case 1:
        {
            ok = true;
            for (int i = 0; i < 6; i++)
            {
                cout << "Введите элемент [" << i + 1 << "]: ";
                cin >> arr[i];
            }
            n = 6;
            break;
        }

        case 2:
        {
            ok = true;
            for (int i = 0; i < 30; i++)
                arr[i] = -100 + rand() % 201;
            n = 30;
            break;
        }

        default:
        {
            cout << "Такой операции не существует! Введите значение еще раз!" << endl;
            break;
        }
        }
    } while (!ok);
   
    cout << endl;
    cout << "Array:" << endl;
    for (int i = 0; i < n; i++) 
    {
        cout << arr[i] << "  ";
    }

    int sumPositive = 0;
    int sumNegative = 0;

    __asm 
    {
        push ebx
        push ecx
        push esi
        push edi
        push edx

        lea ebx, arr
        mov ecx, n
        xor esi, esi
        xor edi, edi
        xor edx, edx

        CALL SumCount
        jmp fin

        SumCount:

        cyc:
        mov edx, [ebx]
        and edx,edx
        jns PositiveAdd
        jmp NegativeAdd

        PositiveAdd:
        add esi, edx
        jmp skip

        NegativeAdd:
        add edi, edx
        jmp skip

        skip:
        add ebx, 4
        dec ecx
        and ecx, ecx
        jnz cyc

        RET

        fin:
        mov sumPositive, esi
        mov sumNegative, edi
        pop edx
        pop edi
        pop esi
        pop ecx
        pop ebx
    }

    cout << endl;
    cout << endl;
    if ((sumPositive != 0) and (sumNegative != 0))
    {
        cout << "Сумма положительных = " << sumPositive << endl;
        cout << "Сумма отрицательных = " << sumNegative << endl;
    }

    if ((sumPositive == 0) and (sumNegative == 0)) 
    {
        cout << "Все числа равны нулю!" << endl;
    }

    if ((sumPositive == 0) and (sumNegative != 0))
    {
        cout << "Нет положительных чисел!" << endl;
        cout << "Сумма отрицательных = " << sumNegative << endl;
    }

    if ((sumPositive != 0) and (sumNegative == 0))
    {
        cout << "Сумма положительных = " << sumPositive << endl;
        cout << "Нет отрицательных чисел!" << endl;
    }

    return 0;
}



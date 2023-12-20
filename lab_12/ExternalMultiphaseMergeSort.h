#include <iostream>
#include <fstream>

int main() {
	std::ifstream input, input1, input2;
	std::ofstream output, output1, output2;
	int a, b = 0;
	int size = 0; // кол-во элементов в файле
	int A_count, B_count, count = 0; // счетчик эл-ов в A, B и в общем
	bool A_is_full, B_is_full, flag = true;

	input.open("input.txt");
	output.open("output.txt");

    // Считываем кол-во символов в input.txt
	while (input >> a) {
		output << a << " ";
		size++;
	}
	input.close();
	output.close();

    // Обработка эл-ов 2k
	for (int timeSize = 1; timeSize < size; timeSize *= 2) {
		input.open("output.txt");
		output1.open("A.txt");
		output2.open("B.txt");
		count = 0;

		while (input >> a)
		{
			count++;
			if (flag)
				output1 << a << " ";
			else
				output2 << a << " ";

			if (count == timeSize)
			{
				count = 0;
				flag = !flag;
			}
		}
		input.close();
		output1.close();
		output2.close();

		input1.open("A.txt");
		input2.open("B.txt");
		output.open("output.txt");

        // Сливаем вспомогательные файлы в один
		if (input1 >> a)
            A_is_full = true;
		else
            A_is_full = false;

		if (input2 >> b)
            B_is_full = true;
		else
            B_is_full = false;

        // Сливаем пары эл-ов в четверки
		for (int i = 0; i < size; i += 2 * timeSize)
		{
            A_count = 0; B_count = 0;
			while (A_count < timeSize && A_is_full && B_count < timeSize && B_is_full)
				if (a < b)
				{
					output << a << " ";
					if (input1 >> a)
                        A_is_full = true;
					else
                        A_is_full = false;
					A_count++;
				}
				else
				{
					output << b << " ";
					if (input2 >> b)
                        B_is_full = true;
					else
                        B_is_full = false;
					B_count++;
				}

                // Удваиваем длину слитых ранее последовательностей
                while (A_count < timeSize && A_is_full)
                {
                    output << a << " ";
                    if (input1 >> a)
                        A_is_full = true;
                    else
                        A_is_full = false;
                    A_count++;
                }
                while (B_count < timeSize && B_is_full)
                {
                    output << b << " ";
                    if (input2 >> b)
                    {
                        B_is_full = true;
                    }
                    else
                    {
                        B_is_full = false;
                    }
                    B_count++;
                }
		}
		input1.close();
		input2.close();
		output.close();
		remove("A.txt");
		remove("B.txt");
	}
	return 0;
}
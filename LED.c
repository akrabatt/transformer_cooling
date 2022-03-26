#include <LPC214X.H>

int x_up_temp = 0;	// переменная для регулирования температуры на увеличение 
int x_down_temp = 0;	// переменная для регулирования температуры на уменьшение
int y_temp = -10;	// переменная для сравнения уставок температуры

int x_up_current = 0;	// переменная для регулирования нагрузки на увеличение 
int x_down_current = 0;	// переменная для регулирования нагрузки на уменьшение
int y_current = -10;	// переменная для сравнения уставок нагрузки

int y_temp_and_current = -10;	// общая переменная для регулирования по температуре и току

int a[] = { 0x1 << 8, 0x1 << 9, 0x1 << 10, 0x1 << 11, 0x1 << 12, 0x1 << 13, 0x1 << 14, 0x1 << 15 };	// массив пинов мк выходных на оборудование

int main(void)
{
	InitLCD();	// инициализация дисплея

	while (1)
	{
		button_temp();	// функция регулирования по температуре
		button_current();	// функция регулирования по нагрузке
	}
}

//// ДОПОЛНИТЕЛЬНЫЕ ФУНКЦИИ ////

//// РЕГУЛИРОВКА ПО ТЕМПЕРАТУРЕ ////
int button_temp()	// функция регулирования температуры
{
	if (~IO0PIN & 0x00000001)	// если кнопка нажата, то перекидываем флаг
	{
		x_up_temp = 1;
	}
	if ((IO0PIN & 0x00000001) && (x_up_temp == 1))	// если кнопка в изначальном положении, то прибавляем к переменной + 1
	{
		y_temp = y_temp + 10;
		switch (y_temp)		// вывод на дисплей
		{
		case 0:
			SetLCD("0t. 1st_pumps ON...................", 30000);
			break;
		case 10:
			SetLCD("10 degrees_temp_ _oil....temp_UP.......", 30000);
			break;
		case 20:
			SetLCD("20 degrees_temp_ _oil....temp_UP.......", 30000);
			break;
		case 30:
			SetLCD("30 degrees_temp_ _oil....temp_UP.......", 30000);
			break;
		case 40:
			SetLCD("40t. 1st_pumps..1st_cooler..ON....", 30000);
			break;
		case 50:
			SetLCD("50 degrees_temp_ _oil....temp_UP......", 30000);
			break;
		case 60:
			SetLCD("60t. 1st_pumps..1.2th_cooler..ON....", 30000);
			break;
		case 70:
			SetLCD("70 degrees_temp_ _oil....temp_UP.....", 30000);
			break;
		case 80:
			SetLCD("80 degrees_temp_ _oil....temp_UP....", 30000);
			break;
		case 90:
			SetLCD("90t. 1st_pumps..1.2.3th_cooler..ON....", 30000);
			break;
		case 100:
			SetLCD("CRITICAL_DAMAGE.!!!!!!!!!!!!!!", 30000);
			break;
		}
		switch (y_temp)		// включение светодиодов, как оборудование
		{
		case 0:		// циркуляционные насосы
			IO0DIR |= a[0];
			IO0CLR |= a[0];

			IO0DIR |= a[1];
			IO0CLR |= a[1];

			IO0DIR |= a[2];
			IO0SET |= a[2];

			IO0DIR |= a[3];
			IO0SET |= a[3];

			IO0DIR |= a[4];
			IO0SET |= a[4];

			IO0DIR |= a[5];
			IO0SET |= a[5];

			IO0DIR |= a[6];
			IO0SET |= a[6];

			IO0DIR |= a[7];
			IO0SET |= a[7];
			break;
		case 40:	// + 1я группа охладителей
			IO0DIR |= a[0];
			IO0CLR |= a[0];

			IO0DIR |= a[1];
			IO0CLR |= a[1];

			IO0DIR |= a[2];
			IO0CLR |= a[2];

			IO0DIR |= a[3];
			IO0CLR |= a[3];

			IO0DIR |= a[4];
			IO0SET |= a[4];

			IO0DIR |= a[5];
			IO0SET |= a[5];

			IO0DIR |= a[6];
			IO0SET |= a[6];

			IO0DIR |= a[7];
			IO0SET |= a[7];
			break;
		case 60:	// + 2я группа охладителей
			IO0DIR |= a[0];
			IO0CLR |= a[0];

			IO0DIR |= a[1];
			IO0CLR |= a[1];

			IO0DIR |= a[2];
			IO0CLR |= a[2];

			IO0DIR |= a[3];
			IO0CLR |= a[3];

			IO0DIR |= a[4];
			IO0CLR |= a[4];

			IO0DIR |= a[5];
			IO0CLR |= a[5];

			IO0DIR |= a[6];
			IO0SET |= a[6];

			IO0DIR |= a[7];
			IO0SET |= a[7];
			break;
		case 90:	// + 3я группа охладителей
			IO0DIR |= a[0];
			IO0CLR |= a[0];

			IO0DIR |= a[1];
			IO0CLR |= a[1];

			IO0DIR |= a[2];
			IO0CLR |= a[2];

			IO0DIR |= a[3];
			IO0CLR |= a[3];

			IO0DIR |= a[4];
			IO0CLR |= a[4];

			IO0DIR |= a[5];
			IO0CLR |= a[5];

			IO0DIR |= a[6];
			IO0CLR |= a[6];

			IO0DIR |= a[7];
			IO0CLR |= a[7];
			break;
		}
		x_up_temp = 0;
	}

	if (~IO0PIN & 0x00000001 << 1)		// понижение температуры, алгоритм тот же что и выше, но на убавление
	{
		x_down_temp = 1;
	}
	if ((IO0PIN & 0x00000001 << 1) && (x_down_temp == 1))
	{
		y_temp = y_temp - 10;
		switch (y_temp)
		{
		case 0:
			SetLCD("0t. 1st_pumps ON...................", 30000);
			break;
		case 10:
			SetLCD("10 degrees_temp_ _oil...temp_LOW.......", 30000);
			break;
		case 20:
			SetLCD("20 degrees_temp_ _oil...temp_LOW.......", 30000);
			break;
		case 30:
			SetLCD("30 degrees_temp_ _oil...temp_LOW.......", 30000);
			break;
		case 40:
			SetLCD("40t. 1st_pumps..1st_cooler..ON....", 30000);
			break;
		case 50:
			SetLCD("50 degrees_temp_ _oil...temp_LOW......", 30000);
			break;
		case 60:
			SetLCD("60t. 1st_pumps..1.2th_cooler..ON....", 30000);
			break;
		case 70:
			SetLCD("70 degrees_temp_ _oil...temp_LOW.....", 30000);
			break;
		case 80:
			SetLCD("80 degrees_temp_ _oil...temp_LOW....", 30000);
			break;
		case 90:
			SetLCD("90t. 1st_pumps..1.2.3th_cooler..ON....", 30000);
			break;
		case 100:
			SetLCD("CRITICAL_DAMAGE.!!!...........", 30000);
			break;
		}
		switch (y_temp)
		{
		case 0:
			IO0DIR |= a[0];
			IO0CLR |= a[0];

			IO0DIR |= a[1];
			IO0CLR |= a[1];

			IO0DIR |= a[2];
			IO0SET |= a[2];

			IO0DIR |= a[3];
			IO0SET |= a[3];

			IO0DIR |= a[4];
			IO0SET |= a[4];

			IO0DIR |= a[5];
			IO0SET |= a[5];

			IO0DIR |= a[6];
			IO0SET |= a[6];

			IO0DIR |= a[7];
			IO0SET |= a[7];
			break;
		case 40:
			IO0DIR |= a[0];
			IO0CLR |= a[0];

			IO0DIR |= a[1];
			IO0CLR |= a[1];

			IO0DIR |= a[2];
			IO0CLR |= a[2];

			IO0DIR |= a[3];
			IO0CLR |= a[3];

			IO0DIR |= a[4];
			IO0SET |= a[4];

			IO0DIR |= a[5];
			IO0SET |= a[5];

			IO0DIR |= a[6];
			IO0SET |= a[6];

			IO0DIR |= a[7];
			IO0SET |= a[7];
			break;
		case 60:
			IO0DIR |= a[0];
			IO0CLR |= a[0];

			IO0DIR |= a[1];
			IO0CLR |= a[1];

			IO0DIR |= a[2];
			IO0CLR |= a[2];

			IO0DIR |= a[3];
			IO0CLR |= a[3];

			IO0DIR |= a[4];
			IO0CLR |= a[4];

			IO0DIR |= a[5];
			IO0CLR |= a[5];

			IO0DIR |= a[6];
			IO0SET |= a[6];

			IO0DIR |= a[7];
			IO0SET |= a[7];
			break;
		case 90:
			IO0DIR |= a[0];
			IO0CLR |= a[0];

			IO0DIR |= a[1];
			IO0CLR |= a[1];

			IO0DIR |= a[2];
			IO0CLR |= a[2];

			IO0DIR |= a[3];
			IO0CLR |= a[3];

			IO0DIR |= a[4];
			IO0CLR |= a[4];

			IO0DIR |= a[5];
			IO0CLR |= a[5];

			IO0DIR |= a[6];
			IO0CLR |= a[6];

			IO0DIR |= a[7];
			IO0CLR |= a[7];
			break;
		}
		x_down_temp = 0;
	}
}

//// РЕГУЛИРОВКА ПО НАГРУЗКЕ ////
int button_current()
{
	if (~IO0PIN & 0x00000001 << 2)
	{
		x_up_current = 1;
	}
	if ((IO0PIN & 0x00000001 << 2) && (x_up_current == 1))
	{
		y_current = y_current + 10;
		switch (y_current)
		{
		case 0:
			SetLCD("0%. 1st_pumps ON...................", 30000);
			break;
		case 10:
			SetLCD("10.persent_load_ _current_UP.......", 30000);
			break;
		case 20:
			SetLCD("20.persent_load_ _current_UP.......", 30000);
			break;
		case 30:
			SetLCD("30.persent_load_ _current_UP.......", 30000);
			break;
		case 40:
			SetLCD("40%. 1st_pumps..1st_cooler..ON....", 30000);
			break;
		case 50:
			SetLCD("50.persent_load_ _current_UP.......", 30000);
			break;
		case 60:
			SetLCD("60.persent_load_ _current_UP.......", 30000);
			break;
		case 70:
			SetLCD("70%. 1st_pumps..1.2th_cooler..ON....", 30000);
			break;
		case 80:
			SetLCD("80.persent_load_ _current_UP.......", 30000);
			break;
		case 90:
			SetLCD("90.persent_load_ _current_UP.......", 30000);
			break;
		case 100:
			SetLCD("FULL_LOAD!!!.all coolers_ON.........", 30000);
			break;
		}
		switch (y_current)
		{
		case 0:
			IO0DIR |= a[0];
			IO0CLR |= a[0];

			IO0DIR |= a[1];
			IO0CLR |= a[1];

			IO0DIR |= a[2];
			IO0SET |= a[2];

			IO0DIR |= a[3];
			IO0SET |= a[3];

			IO0DIR |= a[4];
			IO0SET |= a[4];

			IO0DIR |= a[5];
			IO0SET |= a[5];

			IO0DIR |= a[6];
			IO0SET |= a[6];

			IO0DIR |= a[7];
			IO0SET |= a[7];
			break;
		case 40:
			IO0DIR |= a[0];
			IO0CLR |= a[0];

			IO0DIR |= a[1];
			IO0CLR |= a[1];

			IO0DIR |= a[2];
			IO0CLR |= a[2];

			IO0DIR |= a[3];
			IO0CLR |= a[3];

			IO0DIR |= a[4];
			IO0SET |= a[4];

			IO0DIR |= a[5];
			IO0SET |= a[5];

			IO0DIR |= a[6];
			IO0SET |= a[6];

			IO0DIR |= a[7];
			IO0SET |= a[7];
			break;
		case 70:
			IO0DIR |= a[0];
			IO0CLR |= a[0];

			IO0DIR |= a[1];
			IO0CLR |= a[1];

			IO0DIR |= a[2];
			IO0CLR |= a[2];

			IO0DIR |= a[3];
			IO0CLR |= a[3];

			IO0DIR |= a[4];
			IO0CLR |= a[4];

			IO0DIR |= a[5];
			IO0CLR |= a[5];

			IO0DIR |= a[6];
			IO0SET |= a[6];

			IO0DIR |= a[7];
			IO0SET |= a[7];
			break;
		case 100:
			IO0DIR |= a[0];
			IO0CLR |= a[0];

			IO0DIR |= a[1];
			IO0CLR |= a[1];

			IO0DIR |= a[2];
			IO0CLR |= a[2];

			IO0DIR |= a[3];
			IO0CLR |= a[3];

			IO0DIR |= a[4];
			IO0CLR |= a[4];

			IO0DIR |= a[5];
			IO0CLR |= a[5];

			IO0DIR |= a[6];
			IO0CLR |= a[6];

			IO0DIR |= a[7];
			IO0CLR |= a[7];
			break;
		}
		x_up_current = 0;
	}


	if (~IO0PIN & 0x00000001 << 3)
	{
		x_down_current = 1;
	}
	if ((IO0PIN & 0x00000001 << 3) && (x_down_current == 1))
	{
		y_current = y_current - 10;
		switch (y_current)
		{
		case 0:
			SetLCD("0t. 1st_pumps ON...................", 30000);
			break;
		case 10:
			SetLCD("10.persent_load_ _current_LOW.......", 30000);
			break;
		case 20:
			SetLCD("20.persent_load_ _current_LOW.......", 30000);
			break;
		case 30:
			SetLCD("30.persent_load_ _current_LOW.......", 30000);
			break;
		case 40:
			SetLCD("40t. 1st_pumps..1st_cooler..ON....", 30000);
			break;
		case 50:
			SetLCD("50.persent_load_ _current_LOW.......", 30000);
			break;
		case 60:
			SetLCD("60t. 1st_pumps..1.2th_cooler..ON....", 30000);
			break;
		case 70:
			SetLCD("70.persent_load_ _current_LOW.......", 30000);
			break;
		case 80:
			SetLCD("80.persent_load_ _current_LOW.......", 30000);
			break;
		case 90:
			SetLCD("90t. 1st_pumps..1.2.3th_cooler..ON....", 30000);
			break;
		case 100:
			SetLCD("CRITICAL_DAMAGE.!!!...........", 30000);
			break;
		}
		switch (y_current)
		{
		case 0:
			IO0DIR |= a[0];
			IO0CLR |= a[0];

			IO0DIR |= a[1];
			IO0CLR |= a[1];

			IO0DIR |= a[2];
			IO0SET |= a[2];

			IO0DIR |= a[3];
			IO0SET |= a[3];

			IO0DIR |= a[4];
			IO0SET |= a[4];

			IO0DIR |= a[5];
			IO0SET |= a[5];

			IO0DIR |= a[6];
			IO0SET |= a[6];

			IO0DIR |= a[7];
			IO0SET |= a[7];
			break;
		case 40:
			IO0DIR |= a[0];
			IO0CLR |= a[0];

			IO0DIR |= a[1];
			IO0CLR |= a[1];

			IO0DIR |= a[2];
			IO0CLR |= a[2];

			IO0DIR |= a[3];
			IO0CLR |= a[3];

			IO0DIR |= a[4];
			IO0SET |= a[4];

			IO0DIR |= a[5];
			IO0SET |= a[5];

			IO0DIR |= a[6];
			IO0SET |= a[6];

			IO0DIR |= a[7];
			IO0SET |= a[7];
			break;
		case 70:
			IO0DIR |= a[0];
			IO0CLR |= a[0];

			IO0DIR |= a[1];
			IO0CLR |= a[1];

			IO0DIR |= a[2];
			IO0CLR |= a[2];

			IO0DIR |= a[3];
			IO0CLR |= a[3];

			IO0DIR |= a[4];
			IO0CLR |= a[4];

			IO0DIR |= a[5];
			IO0CLR |= a[5];

			IO0DIR |= a[6];
			IO0SET |= a[6];

			IO0DIR |= a[7];
			IO0SET |= a[7];
			break;
		case 100:
			IO0DIR |= a[0];
			IO0CLR |= a[0];

			IO0DIR |= a[1];
			IO0CLR |= a[1];

			IO0DIR |= a[2];
			IO0CLR |= a[2];

			IO0DIR |= a[3];
			IO0CLR |= a[3];

			IO0DIR |= a[4];
			IO0CLR |= a[4];

			IO0DIR |= a[5];
			IO0CLR |= a[5];

			IO0DIR |= a[6];
			IO0CLR |= a[6];

			IO0DIR |= a[7];
			IO0CLR |= a[7];
			break;
		}
		x_down_current = 0;
	}
}

//// ИНИЦИАЛИЗАЦИЯ ДИСПЛЕЯ ////
int InitLCD()
{
	int long cnt = 0;
	int data[4] = { (0x07 << 19),(0x0C << 16),(0x01 << 16),(0x06 << 16) };
	int i = 0;
	IODIR0 = (1 << 22) | (1 << 30);		// установка P0.22 и P0.30 как
																				//выхо¬дов 
	IODIR1 = (0x3FF << 16);			// установка P1.16 – P1.25 как
																				//выхо¬дов
	IOSET0 = (1 << 30);				// включение подсветки
	for (cnt = 0; cnt < 2000; cnt++);		// задержка (в дальнейшем ком-¬
																			   //ментироваться не будет)
	while (i != 4)
	{
		IOSET1 = (1 << 25);				// 2-строковый режим, 5 ? 7 точек,
									   //вклю¬чить дисплей, выключить
									 //мигание и курсор, выключить
								   //удержание, режим «слева-//направо»
		IOSET1 = data[i];
		IOCLR1 = (1 << 25);
		for (cnt = 0; cnt < 2000; cnt++);
		IOCLR1 = 0xFFFFFF;			// очистка регистра выхода пор¬-
																			   //та P1
		i++;
	}
	IOSET1 = (1 << 24);				// разрешение ввода данных
	return 0;
}

//// ЗАДАТЬ ЗНАЧЕНИЕ ДЛЯ ДИСПЛЕЯ ////
int SetLCD(char str[], int skorost)
{
	int count = 0;
	int long cnt = 0;
	while (str[count] != '\0')
	{
		IOSET1 = (1 << 25);
		IOSET1 = (str[count] << 16);			// посимвольный вывод элемен-
						 //тов массива str [номер элемента]
		IOCLR1 = (1 << 25);
		IOCLR1 = (0xFF << 16);
		for (cnt = 0; cnt < skorost; cnt++);

		/* Переключение во вторую строку при достижении 15-го элемента массива*/

		if (count == 15)
		{
			IOCLR1 = 0x1FFFFFF;
			IOSET1 = (1 << 25);
			IOSET1 = 0xC00000;
			IOCLR1 = (1 << 25);
			for (cnt = 0; cnt < 2000; cnt++);
			IOCLR1 = 0x1FFFFFF;
			IOSET1 = (1 << 24);
		}
		count++;
	}
	IOCLR1 = 0x1FFFFFF;
	IOSET1 = (1 << 25);
	IOSET1 = 0x020000;
	IOCLR1 = (1 << 25);
	for (cnt = 0; cnt < 2000; cnt++);
	IOCLR1 = 0x1FFFFFF;
	IOSET1 = (1 << 24);
	return 0;
}





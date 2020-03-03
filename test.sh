#!/bin/bash
echo "Программа установки прав доступа к файлу"
echo "Данная программа позволяет устанвоить права доступа к необходимому файлу (далее второй файл) по образцу другого файла (далее первый файл)"
echo "Раработчик: Александра Шатрова"
echo " "

function input_1 {
echo -n "Введите путь к первому файлу: "
read myfile_1
if [ -n "$myfile_1" ]
then 
if test -f $myfile_1
then
input_2
else
test -f $myfile_1
echo "Файла $myfile_1 не существует" >&2
replay 1
fi
else
input_1
fi
}

function input_2 {
echo -n "Введите путь ко второму файлу: " 
read myfile_2
if [ -n "$myfile_2" ]
then 
if test -f $myfile_2
then
next
else
echo "Файла $myfile_2 не существует" >&2
replay 2
fi
else
input_2
fi
}

function replay {
echo -n "Хотите ввести путь к файлу ещё раз? [y/n] "
read answer
if [ $answer = "y" ]
then
input_$1
elif [ $answer = "n" ]
then
exit_pr
else
echo "Неправильный ввод!" >&2
replay $1
fi
}

function next {
if [ $myfile_1 = $myfile_2 ]
then
echo "Файлы совпадают!" >&2
replay 2
else
echo -n "Вы уверены, что хотите установить права доступа к $myfile_2 по образцу файла $myfile_1? [y/n] "
read answers
if [ $answers = "y" ]
then
chmod --reference=$myfile_1 $myfile_2 >&2
res=$?
if [ $res = "0" ]
then 
echo "Установка прав успешна завершена"
fi
end
elif [ $answers = "n" ]
then
exit_pr
else
echo "Неправильный ввод!" >&2
next
fi
fi
}

function end {
echo -n "Хотите установить права доступа на другой файл? [y/n] "
read answe
if [ $answe = "y" ]
then
input_1
elif [ $answe = "n" ]
then
exit_pr
else
echo "Неправильный ввод!" >&2
end
fi
}

function exit_pr {
echo -n "Хотите выйти из программы? [y/n] "
read answer_exit
if [ $answer_exit = "y" ]
then
echo "Выход из программы ... "
exit
elif [ $answer_exit = "n" ]
then
echo "-------"
input_1
else
echo "Неправильный ввод!" >&2
exit_pr
fi
}

input_1
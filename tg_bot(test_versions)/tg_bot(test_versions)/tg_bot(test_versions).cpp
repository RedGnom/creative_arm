
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <string>
#include "buttons.h"
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <filesystem>
#include <stdio.h>
#include <tgbot/tgbot.h>
#include <Windows.h>
#include <chrono>
#include <iomanip>
#include <time.h>



//Преобразование utf8(telegram) в w1251 для чтения в windows
std::string utf8_to_windows1251(const std::string& utf8String) {
    // Преобразование в широкую строку (UTF-16)
    int wideSize = MultiByteToWideChar(CP_UTF8, 0, utf8String.c_str(), -1, nullptr, 0);
    wchar_t* wideString = new wchar_t[wideSize];
    MultiByteToWideChar(CP_UTF8, 0, utf8String.c_str(), -1, wideString, wideSize);

    // Преобразование в Windows-1251
    int ansiSize = WideCharToMultiByte(1251, 0, wideString, -1, nullptr, 0, nullptr, nullptr);
    char* ansiString = new char[ansiSize];
    WideCharToMultiByte(1251, 0, wideString, -1, ansiString, ansiSize, nullptr, nullptr);

    std::string result(ansiString);

    delete[] wideString;
    delete[] ansiString;

    return result;
}
//w1251 в utf8
std::string windows1251_to_utf8(const std::string& windows1251String) {
    int wideSize = MultiByteToWideChar(1251, 0, windows1251String.c_str(), -1, nullptr, 0);
    wchar_t* wideString = new wchar_t[wideSize];
    MultiByteToWideChar(1251, 0, windows1251String.c_str(), -1, wideString, wideSize);

    // Преобразование в UTF-8
    int utf8Size = WideCharToMultiByte(CP_UTF8, 0, wideString, -1, nullptr, 0, nullptr, nullptr);
    char* utf8String = new char[utf8Size];
    WideCharToMultiByte(CP_UTF8, 0, wideString, -1, utf8String, utf8Size, nullptr, nullptr);

    std::string result(utf8String);

    delete[] wideString;
    delete[] utf8String;

    return result;
}

//Флаги состояний
using namespace std;
using namespace TgBot;
bool casserole_flag = false;
bool breakfast_1 = false;
bool porridge = false;
bool meal_flag = false;
bool borsch_flag = false;
bool shawarma_flag = false;
bool lasagna_flag = false;
bool Tagliatelle_flag = false;
bool fillet_flag = false;


//Флаги состояний и проверка пароля
string expect_pass;
bool Wait_Name = true;
bool Wait_password = false;

int main() {
    setlocale(LC_ALL, "RU");
    system("chcp 1251>nul");
    TgBot::Bot bot("");

    //Привязка кнопок к различным видам подтекстовых клавиатур
    Buttons buttons;
    InlineKeyboardMarkup::Ptr keyboard(new InlineKeyboardMarkup);
    InlineKeyboardMarkup::Ptr menu_positions(new InlineKeyboardMarkup);
    InlineKeyboardMarkup::Ptr dish_interact(new InlineKeyboardMarkup);
    InlineKeyboardMarkup::Ptr return_menu(new InlineKeyboardMarkup);
    vector<InlineKeyboardButton::Ptr> row0 = {buttons.menuButton,buttons.balanceButton};
    vector<InlineKeyboardButton::Ptr> row1 = {buttons.breakfast_1,buttons.porridge, buttons.casserole};
    vector<InlineKeyboardButton::Ptr> row2 = { buttons.meal, buttons.borsch, buttons.shawarma};
    vector<InlineKeyboardButton::Ptr> row5 = { buttons.lasagna, buttons.Tagliatelle, buttons.fillet};
    vector<InlineKeyboardButton::Ptr> row3;
    vector<InlineKeyboardButton::Ptr> row4;
    row4.push_back(buttons.back_menu);
    menu_positions->inlineKeyboard.push_back(row1);
    menu_positions->inlineKeyboard.push_back(row2);
    menu_positions->inlineKeyboard.push_back(row5);

    row3.push_back(buttons.purchase);
    row3.push_back(buttons.backButton);

    //Ссылки на фото для блюд
    const string photoFilePath = "breakfast_1.jpg";
    const string photoMimeType = "image/jpeg";
    const string kot = "porridge.jpg";
    const string casserole = "casserole.jpg";
    const string meal = "meal.jpg";
    const string borsch = "borsch.jpg";
    const string shawarma = "shawarma.jpg";
    const string lasagna = "lasagna.jpg";
    const string Tagliatelle = "Tagliatelle.jpg";
    const string fillet = "fillet.jpg";

    //Имя пользователя
    string dirname;

    keyboard->inlineKeyboard.push_back(row0);
    dish_interact->inlineKeyboard.push_back(row3);
    return_menu->inlineKeyboard.push_back(row4);

    //Начало взаимодействия с ботом
    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, u8"Здравствуйте");
        bot.getApi().sendMessage(message->chat->id, u8"Введите пожайлуста имя, под которым вас зарегистрировали");
        });
    //Структура для принятия сообщений для пользователя
    bot.getEvents().onAnyMessage([&bot, &dirname, &keyboard](TgBot::Message::Ptr message) {
        if (StringTools::startsWith(message->text, "/start")) {
            return;
        }
        //Ожидание ввода существующиего имени от пользователя
        if (Wait_Name) {
            dirname = utf8_to_windows1251(message->text);
            replace(dirname.begin(), dirname.end(), ' ', '_');
            filesystem::path dir = dirname; //Переход в папку с именем пользователя
            string path = "A:\\projects\\Creative_work(1.0)\\Creative_work(1.0)\\" + dirname + "\\password.txt";
            ifstream passwordFile(path);
            string line;
            //Проверка на наличие человека в записях
            if (passwordFile.is_open()) {
                getline(passwordFile, line);
                bot.getApi().sendMessage(message->chat->id, u8"Введите пароль, который вам дал администратор: ");
                
                expect_pass = line;
                passwordFile.close();
                //Переключение флагов состония
                Wait_Name = false;
                Wait_password = true;
            }
            else {
                bot.getApi().sendMessage(message->chat->id, u8" Данный пользователь отсутствует: ");
            }
        }
        //Проверка введеного пароля с заранее записанным
        else if (Wait_password) {
            string Password_by_user = utf8_to_windows1251(message->text);
            //Проверка пароля и вызов кнопок для взаимодействия
            if (Password_by_user == expect_pass) {
                bot.getApi().sendMessage(message->chat->id, u8" Добро пожаловать: ", false, 0, keyboard, "Markdown");
                Wait_password = false;
            }
            else {
                bot.getApi().sendMessage(message->chat->id, u8" Пароль неверный, введите еще раз: ");
            }
        }
        });


    
    //Реализация кнопок для меню и баланса
    bot.getEvents().onCallbackQuery([&bot, &menu_positions, &keyboard, &dirname](CallbackQuery::Ptr query) {
        if (StringTools::startsWith(query->data, "show_menu")) {
            bot.getApi().sendMessage(query->message->chat->id, u8"Разные позиции из меню", false, 0, menu_positions, "Markdown");
        }
        if (StringTools::startsWith(query->data, "show_balance")) {
            string path = "A:\\projects\\Creative_work(1.0)\\Creative_work(1.0)\\" + dirname + "\\balance.txt";
            ifstream balanceFile(path);
            string current_balance;
            balanceFile >> current_balance;
            balanceFile.close();


            bot.getApi().sendMessage(query->message->chat->id, u8"Ваш баланс на данный момент: " + current_balance + u8" рублей", false, 0, keyboard);
        }
        });
    //Структура для блюд
    bool delete_msg = false; //Флаг обеспечивающий удаление сообщений при нажатии кнопки назад
    bot.getEvents().onCallbackQuery([&bot, &photoFilePath, &photoMimeType,&delete_msg, &dish_interact,
        &kot,&casserole, &meal, &borsch, &shawarma, &lasagna, &Tagliatelle, &fillet](CallbackQuery::Ptr query) {

        if (StringTools::startsWith(query->data, "breakfast_1")) {
            bot.getApi().sendPhoto(query->message->chat->id, InputFile::fromFile(photoFilePath, photoMimeType)); //Вывод фото блюда
            bot.getApi().sendMessage(query->message->chat->id, u8"Состав: Полукопчёная колбаска с сыром и кинзой, обжаренный бекон, пышная картофельная вафля, глазунья и фасоль в томатном соусе, томатами Черри с зеленью. ");
            bot.getApi().sendMessage(query->message->chat->id, u8"Калорийность: 197 ккал на 100гр");
            bot.getApi().sendMessage(query->message->chat->id, u8"Цена: 440 рублей", false, 0, dish_interact, "Markdown");
            breakfast_1 = true; //Флаг состояния для дальнейшей обработки
            delete_msg = true;
        }
        else if (StringTools::startsWith(query->data, "porridge")) {
            bot.getApi().sendPhoto(query->message->chat->id, InputFile::fromFile(kot, photoMimeType));
            bot.getApi().sendMessage(query->message->chat->id, u8"Питательная мультизлаковая каша, сваренная на молоке и украшенная гранолой и россыпью свежих ягод: клубникой, голубикой");
            bot.getApi().sendMessage(query->message->chat->id, u8"Калорийность: 83 ккал на 100гр");
            bot.getApi().sendMessage(query->message->chat->id, u8"Цена: 350 рублей", false, 0, dish_interact, "Markdown");
            porridge = true;
            delete_msg = true;
        }
        else if (StringTools::startsWith(query->data, "casserole")) {
            bot.getApi().sendPhoto(query->message->chat->id, InputFile::fromFile(casserole, photoMimeType));
            bot.getApi().sendMessage(query->message->chat->id, u8"Нежная запеканка на твороге с кусочками свежей груши. По желанию вы можете добавить к ней варенье, сгущённое молоко или любой другой наполнитель.");
            bot.getApi().sendMessage(query->message->chat->id, u8"Калорийность: 121 ккал на 100гр");
            bot.getApi().sendMessage(query->message->chat->id, u8"Цена: 217 рублей", false, 0, dish_interact, "Markdown");
            casserole_flag = true;
            delete_msg = true;
        }
        else if (StringTools::startsWith(query->data, "meal")) {
            bot.getApi().sendPhoto(query->message->chat->id, InputFile::fromFile(meal, photoMimeType));
            bot.getApi().sendMessage(query->message->chat->id, u8"Мягкая говядина высшего качества, тушённая со свежими шампиньонами и сочным репчатым луком в натуральных сливках. Сливочное пюре, приготовленное из отборного картофеля, идеально сочетается с мясом. Блюдо приправлено соевым соусом.");
            bot.getApi().sendMessage(query->message->chat->id, u8"Калорийность: 144 ккал на 100гр");
            bot.getApi().sendMessage(query->message->chat->id, u8"Цена: 320 рублей", false, 0, dish_interact, "Markdown");
            meal_flag = true;
            delete_msg = true;
        }
        else if (StringTools::startsWith(query->data, "borsch")) {
            bot.getApi().sendPhoto(query->message->chat->id, InputFile::fromFile(borsch, photoMimeType));
            bot.getApi().sendMessage(query->message->chat->id, u8"Ароматный и густой красный борщ по традиционному рецепту. Заботливо приготовлен на крепком и прозрачном говяжьем бульоне, с щедрой заправкой из сладкой свёклы, моркови, картофеля, капусты и болгарского перца.");
            bot.getApi().sendMessage(query->message->chat->id, u8"Калорийность: 70 ккал на 100гр");
            bot.getApi().sendMessage(query->message->chat->id, u8"Цена: 221 рублей", false, 0, dish_interact, "Markdown");
            borsch_flag = true;
            delete_msg = true;
        }
        else if (StringTools::startsWith(query->data, "shawarma")) {
            bot.getApi().sendPhoto(query->message->chat->id, InputFile::fromFile(shawarma, photoMimeType));
            bot.getApi().sendMessage(query->message->chat->id, u8"Сочная шаурма с запечёнными куриными бёдрышками. Приготовлена по-грузински: с целым букетом кавказских трав и пикантной аджикой. Завёрнута в тонкий пшеничный лаваш и слегка обжарена на гриле.");
            bot.getApi().sendMessage(query->message->chat->id, u8"Калорийность: 254.16 ккал на 100гр");
            bot.getApi().sendMessage(query->message->chat->id, u8"Цена: 298 рублей", false, 0, dish_interact, "Markdown");
            shawarma_flag = true;
            delete_msg = true;
        }
        else if (StringTools::startsWith(query->data, "lasagna")) {
            bot.getApi().sendPhoto(query->message->chat->id, InputFile::fromFile(lasagna, photoMimeType));
            bot.getApi().sendMessage(query->message->chat->id, u8"Классическое блюдо итальянской кухни. Между отваренными листами пасты находится толстый слой начинки из сочной говядины в соусе «болоньезе». Мясо щедро приправлено свежими прованскими травами, которые придают блюду выразительный пряный вкус. Запекается лазанья под соусом «бешамель», смешанным с тёртым пармезаном.");
            bot.getApi().sendMessage(query->message->chat->id, u8"Калорийность: 177.6 ккал на 100гр");
            bot.getApi().sendMessage(query->message->chat->id, u8"Цена: 358 рублей", false, 0, dish_interact, "Markdown");
            lasagna_flag = true;
            delete_msg = true;
        }
        else if (StringTools::startsWith(query->data, "Tagliatelle")) {
            bot.getApi().sendPhoto(query->message->chat->id, InputFile::fromFile(Tagliatelle, photoMimeType));
            bot.getApi().sendMessage(query->message->chat->id, u8"Плотная паста с кусочками курицы в нежнейшем сырном соусе. Соус изготовлен на основе жирных сливок и сыра с благородной голубой плесенью. Изысканный, слегка пикантный вкус блюда не оставит равнодушными даже искушённого гурмана.");
            bot.getApi().sendMessage(query->message->chat->id, u8"Калорийность: 183.3 ккал на 100гр");
            bot.getApi().sendMessage(query->message->chat->id, u8"Цена: 288 рублей", false, 0, dish_interact, "Markdown");
            Tagliatelle_flag = true;
            delete_msg = true;
        }
        else if (StringTools::startsWith(query->data, "fillet")) {
            bot.getApi().sendPhoto(query->message->chat->id, InputFile::fromFile(fillet, photoMimeType));
            bot.getApi().sendMessage(query->message->chat->id, u8"Филе атлантической сёмги, приготовленное с брокколи, цветной капустой и ломтиками моркови на пару. Чтобы блюдо сохранило свой натуральный вкус, мы приправили его небольшим количеством соли и отказались от других специй. Для больше сочности рекомендуем полить рыбу небольшим количеством лимонного сока.");
            bot.getApi().sendMessage(query->message->chat->id, u8"Калорийность: 96.4 ккал на 100гр");
            bot.getApi().sendMessage(query->message->chat->id, u8"Цена: 490 рублей", false, 0, dish_interact, "Markdown");
            fillet_flag = true;
            delete_msg = true;
        }

        });
    
    
    //Принятие блюд и списывание денег с баланса
    bool successful_payment = true;
    bot.getEvents().onCallbackQuery([&bot, &delete_msg, &dirname, &keyboard, &successful_payment](CallbackQuery::Ptr query) {
        //Выдача локального времени
        auto now = std::chrono::system_clock::now();
        std::time_t time_now = std::chrono::system_clock::to_time_t(now);
        struct tm timeinfo;
        localtime_s(&timeinfo, &time_now);
        //Нажатие на кнопку purchase и обработка(у каждого блюда разная)
        if (StringTools::startsWith(query->data, "purchase")) {
            //Открытие файла баланса из папки пользователя
            string path = "A:\\projects\\Creative_work(1.0)\\Creative_work(1.0)\\" + dirname + "\\balance.txt";
            ifstream balanceFile(path);
            int new_balance;
            //Считывание текущего
            balanceFile >> new_balance;
            balanceFile.close();
            if (new_balance <= 0) {
                successful_payment = false;
            }
            //Вывод администратору и пользователю сообщения о покупке
            if (breakfast_1 && successful_payment) {
                //Обновление баланса
                new_balance -= 440;
                bot.getApi().sendMessage(query->message->chat->id, u8"Куплен английский завтрак");
                cout << std::put_time(&timeinfo, "%Y-%m-%d %X") <<"   Клиент: " << dirname << "  Заказал англйиский завтрак" << endl;
                //Сброс флага в изначальное положение
                breakfast_1 = false;
            }
            if (porridge && successful_payment) {
                new_balance -= 350;
                bot.getApi().sendMessage(query->message->chat->id, u8"Куплена злаковая каша");
                cout << std::put_time(&timeinfo, "%Y-%m-%d %X") << "   Клиент: " << dirname << "  Заказал злаковую кашу" << endl;
                porridge = false;
            }
            if (casserole_flag && successful_payment) {
                new_balance -= 217;
                bot.getApi().sendMessage(query->message->chat->id, u8"Куплена запеканка");
                cout << std::put_time(&timeinfo, "%Y-%m-%d %X") << "   Клиент: " << dirname << "  Заказал запеканку" << endl;
                
                casserole_flag = false;
            }
            if (meal_flag && successful_payment) {
                new_balance -= 320;
                bot.getApi().sendMessage(query->message->chat->id, u8"Куплен бифстроганов с пюре");
                cout << std::put_time(&timeinfo, "%Y-%m-%d %X") << "   Клиент: " << dirname << "  Заказал бефстроганов из говядины с картофельным пюре" << endl;

                meal_flag = false;
            }
            if (borsch_flag && successful_payment) {
                new_balance -= 221;
                bot.getApi().sendMessage(query->message->chat->id, u8"Куплен борщ с говядиной");
                cout << std::put_time(&timeinfo, "%Y-%m-%d %X") << "   Клиент: " << dirname << "  Заказал борщ с говядиной" << endl;

                borsch_flag = false;
            }
            if (shawarma_flag && successful_payment) {
                new_balance -= 298;
                bot.getApi().sendMessage(query->message->chat->id, u8"Куплена шаверма грузинская");
                cout << std::put_time(&timeinfo, "%Y-%m-%d %X") << "   Клиент: " << dirname << "  Заказал шаверму грузинскую" << endl;

                shawarma_flag = false;
            }
            if (lasagna_flag && successful_payment) {
                new_balance -= 358;
                bot.getApi().sendMessage(query->message->chat->id, u8"Куплена лазанья");
                cout << std::put_time(&timeinfo, "%Y-%m-%d %X") << "   Клиент: " << dirname << "  Заказал лазанью мясную" << endl;

                lasagna_flag = false;
            }
            if (Tagliatelle_flag && successful_payment) {
                new_balance -= 288;
                bot.getApi().sendMessage(query->message->chat->id, u8"Куплена Тальятелле с курицей в сырном соусе");
                cout << std::put_time(&timeinfo, "%Y-%m-%d %X") << "   Клиент: " << dirname << "  Заказал Тальятеллью с курицей в сырном соусе" << endl;

                Tagliatelle_flag = false;
            }
            if (fillet_flag && successful_payment) {
                new_balance -= 490;
                bot.getApi().sendMessage(query->message->chat->id, u8"Куплено филе семги с овощами");
                cout << std::put_time(&timeinfo, "%Y-%m-%d %X") << "   Клиент: " << dirname << "  Заказал филе семги с овощами" << endl;

                fillet_flag = false;
            }

            ofstream balanceFile2(path);
            if (successful_payment) {
                //Звуковое оповещение администатора
                bot.getApi().sendMessage(query->message->chat->id, u8"Выполнен возврат к меню", false, 0, keyboard, "Markdown");
                cout << '\a';
                Beep(523, 500);
                Beep(523, 500);
                Beep(523, 500);
  
                balanceFile2 << new_balance;
            }
            //Если средства ушли в минус, то выводит сообщение об ошибке
            else {
                bot.getApi().sendMessage(
                    query->message->chat->id,
                    u8"Средства на вашем счету закончились.\n"
                    "Чтобы посмотреть баланс - следует нажать на кнопку текущий баланс", false, 0, keyboard, "Markdown"
                );

                balanceFile2 << new_balance;
            }
            balanceFile2.close();
            

        }
        //Удаление сообщений по кнопке назад
        if (StringTools::startsWith(query->data, "back")) {
            if (delete_msg) {
                for (int i = 0; i < 4; i++) {
                    bot.getApi().deleteMessage(query->message->chat->id, query->message->messageId-i);
                }
                
            }
            //Сброс флагов, так как действие отменено
            casserole_flag = false;
            breakfast_1 = false;
            porridge = false;
            meal_flag = false;
            borsch_flag = false;
            shawarma_flag = false;
            lasagna_flag = false;
            Tagliatelle_flag = false;
            fillet_flag = false;
        }

        });
    
    signal(SIGINT, [](int s) {
        printf("SIGINT got\n");
        exit(0);
        });
    //Метод для приема сообщений и команд ботом
    try {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        bot.getApi().deleteWebhook();

        TgLongPoll longPoll(bot);
        while (true) {
            /*printf("Long poll started\n");*/
            longPoll.start();
        }
    }
    //Отлов ошибок
    catch (exception& e) {
        printf("error: %s\n", e.what());
    }

    return 0;
}

#pragma once
#include <string>
#include <vector>
#include <tgbot/tgbot.h>
//Кнопки, которые рисуются под сообщениями
struct Buttons {
    TgBot::InlineKeyboardButton::Ptr fillet;
    TgBot::InlineKeyboardButton::Ptr casserole;
    TgBot::InlineKeyboardButton::Ptr lasagna;
    TgBot::InlineKeyboardButton::Ptr Tagliatelle;
    TgBot::InlineKeyboardButton::Ptr shawarma;
    TgBot::InlineKeyboardButton::Ptr borsch;
    TgBot::InlineKeyboardButton::Ptr meal;
    TgBot::InlineKeyboardButton::Ptr balanceButton;
    TgBot::InlineKeyboardButton::Ptr menuButton;
    TgBot::InlineKeyboardButton::Ptr breakfast_1;
    TgBot::InlineKeyboardButton::Ptr porridge;
    TgBot::InlineKeyboardButton::Ptr purchase;
    TgBot::InlineKeyboardButton::Ptr backButton;
    TgBot::InlineKeyboardButton::Ptr back_menu;

    Buttons() {
        fillet = std::make_shared<TgBot::InlineKeyboardButton>();
        fillet->text = u8"Филе семги с овощами";
        fillet->callbackData = "fillet";

        Tagliatelle = std::make_shared<TgBot::InlineKeyboardButton>();
        Tagliatelle->text = u8"Тальятелле с курицей";
        Tagliatelle->callbackData = "Tagliatelle";


        lasagna = std::make_shared<TgBot::InlineKeyboardButton>();
        lasagna->text = u8"Лазанья мясная";
        lasagna->callbackData = "lasagna";

        shawarma = std::make_shared<TgBot::InlineKeyboardButton>();
        shawarma->text = u8"Шаурма грузинская";
        shawarma->callbackData = "shawarma";

        borsch = std::make_shared<TgBot::InlineKeyboardButton>();
        borsch->text = u8"Борщ с говядиной";
        borsch->callbackData = "borsch";

        meal = std::make_shared<TgBot::InlineKeyboardButton>();
        meal->text = u8"Бефстроганов из говядины с картофельным пюре";
        meal->callbackData = "meal";

        casserole = std::make_shared<TgBot::InlineKeyboardButton>();
        casserole->text = u8"Запеканка творожная с грушей";
        casserole->callbackData = "casserole";


        back_menu = std::make_shared<TgBot::InlineKeyboardButton>();
        back_menu->text = u8"Возврат к меню";
        back_menu->callbackData = "back_menu";

        backButton = std::make_shared<TgBot::InlineKeyboardButton>();
        backButton->text = u8"Назад";
        backButton->callbackData = "back";

        purchase = std::make_shared<TgBot::InlineKeyboardButton>();
        purchase->text = u8"Заказать";
        purchase->callbackData = "purchase";

        balanceButton = std::make_shared<TgBot::InlineKeyboardButton>();
        balanceButton->text = u8"Текущий баланс";
        balanceButton->callbackData = "show_balance";

        menuButton = std::make_shared<TgBot::InlineKeyboardButton>();
        menuButton->text = u8"Меню";
        menuButton->callbackData = "show_menu";

        breakfast_1 = std::make_shared<TgBot::InlineKeyboardButton>();
        breakfast_1->text = u8"Анг. завтрак";
        breakfast_1->callbackData = "breakfast_1";

        porridge = std::make_shared<TgBot::InlineKeyboardButton>();
        porridge->text = u8"Злаковая каша";
        porridge->callbackData = "porridge";
    }
};
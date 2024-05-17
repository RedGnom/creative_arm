#pragma once
#include <string>
#include <vector>
#include <tgbot/tgbot.h>
//������, ������� �������� ��� �����������
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
        fillet->text = u8"���� ����� � �������";
        fillet->callbackData = "fillet";

        Tagliatelle = std::make_shared<TgBot::InlineKeyboardButton>();
        Tagliatelle->text = u8"���������� � �������";
        Tagliatelle->callbackData = "Tagliatelle";


        lasagna = std::make_shared<TgBot::InlineKeyboardButton>();
        lasagna->text = u8"������� ������";
        lasagna->callbackData = "lasagna";

        shawarma = std::make_shared<TgBot::InlineKeyboardButton>();
        shawarma->text = u8"������ ����������";
        shawarma->callbackData = "shawarma";

        borsch = std::make_shared<TgBot::InlineKeyboardButton>();
        borsch->text = u8"���� � ���������";
        borsch->callbackData = "borsch";

        meal = std::make_shared<TgBot::InlineKeyboardButton>();
        meal->text = u8"������������ �� �������� � ������������ ����";
        meal->callbackData = "meal";

        casserole = std::make_shared<TgBot::InlineKeyboardButton>();
        casserole->text = u8"��������� ��������� � ������";
        casserole->callbackData = "casserole";


        back_menu = std::make_shared<TgBot::InlineKeyboardButton>();
        back_menu->text = u8"������� � ����";
        back_menu->callbackData = "back_menu";

        backButton = std::make_shared<TgBot::InlineKeyboardButton>();
        backButton->text = u8"�����";
        backButton->callbackData = "back";

        purchase = std::make_shared<TgBot::InlineKeyboardButton>();
        purchase->text = u8"��������";
        purchase->callbackData = "purchase";

        balanceButton = std::make_shared<TgBot::InlineKeyboardButton>();
        balanceButton->text = u8"������� ������";
        balanceButton->callbackData = "show_balance";

        menuButton = std::make_shared<TgBot::InlineKeyboardButton>();
        menuButton->text = u8"����";
        menuButton->callbackData = "show_menu";

        breakfast_1 = std::make_shared<TgBot::InlineKeyboardButton>();
        breakfast_1->text = u8"���. �������";
        breakfast_1->callbackData = "breakfast_1";

        porridge = std::make_shared<TgBot::InlineKeyboardButton>();
        porridge->text = u8"�������� ����";
        porridge->callbackData = "porridge";
    }
};
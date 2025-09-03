#include <ctype.h>

#include "CUI_PRIVATE.H"
#include "CUI_INPUT.H"


int cui_read(con_ui *cui,
             char *Buffer, size_t MaxLength,
             input_rules Rule)
{
    gets_s(Buffer, MaxLength);

    //return cui_read_ex(cui, Buffer, MaxLength, Rule, 0xFF);
}

/*
static
input_e _read_single_key()
{
    INPUT_RECORD input_buffer = { 0 };
    DWORD read_counter = 0;

    while (true)
    {
        ReadConsoleInputA(h_input, &input_buffer, 1, &read_counter);

        if (input_buffer.EventType != KEY_EVENT)
            continue;

        KEY_EVENT_RECORD event = input_buffer.Event.KeyEvent;

        if (!event.bKeyDown)
            continue;

        input_e ret = IS_SPECIAL;

        switch (event.wVirtualKeyCode)
        {
        case VK_RETURN:
            return SIGNAL_ENTER;
        case VK_LEFT:
            ret |= CURSOR_LEFT;
            break;
        case VK_RIGHT:
            ret |= CURSOR_RIGHT;
            break;
        case VK_BACK:
            ret |= SIGNAL_BACK;
            break;
        case VK_SPACE:
            ret |= SIGNAL_SPACE;
            break;
        default:
            ret = 0;
        }

        if (event.dwControlKeyState & LEFT_CTRL_PRESSED
        || event.dwControlKeyState & RIGHT_CTRL_PRESSED) {
            ret |= ( IS_SPECIAL | MODIFY_CTRL );
        }

        if (isprint(event.uChar.AsciiChar)) {
            ret += event.uChar.AsciiChar;
        }

        return ret;
    }
}


int cui_read_ex(con_ui *cui, 
                char *Buffer, size_t MaxLength, 
                input_rules Rule, char TerminationChar)
{
    int length = 0;
    int cursor = 0;


    while (length <= MaxLength)
    {
        input_e input = _read_single_key();
        
        char c = input & 0xFF;

        if (input & IS_SPECIAL) {

            if (input & SIGNAL_ENTER) {
                Buffer[length] = '\0';
                return length;
            }

            if (input & SIGNAL_BACK) 
            {
                if (cursor > 0) 
                {
                    for (int i = cursor - 1; i < length; i++) {
                        Buffer[i] = Buffer[i + 1];
                    }

                    length -= 1;
                    cursor -= 1;
                    Buffer[length] = '\0';
                    cui_clear_char(cui);
                    cui_inc_x(cui);
                }

                continue;
            }

            if (input & CURSOR_LEFT) 
            {    
                if (cursor > 0) {
                    cursor -= 1;
                    cui_dec_x(cui);
                }
                
                continue;
            }

            if (input & CURSOR_RIGHT) 
            {
                if (cursor < length) {
                    cursor += 1;
                    cui_inc_x(cui);
                }
            }
        }


        if (c == TerminationChar) {
            return length;
        }

        if (breaks_rule(c, Rule)) {
            continue;
        }

        Buffer[cursor++] = c;
        cursor += 1;

        cui_emit(cui, c);

        if (cursor == length) {
            continue;
        }

        cui_draw(cui, Buffer + cursor);
    }

    return length;
}

bool breaks_rule(char input, enum input_rules Rule)
{
    if (Rule == NONE)
        return false;

    if (Rule == FILENAME)
    {
        switch (input)
        {
        case '\\':
        case '/':
        case ':':
        case '*':
        case '?':
        case '"':
        case '<':
        case '>':
        case '|':
            return true;
        default:
            return false;
        }
    }

    if (Rule == NUMBER)
    {
        if (!( input >= 0 && input <= 9 ))
            return true;
    }
    if (Rule == TIMESTAMP)
    {
        if (!( input >= 0 && input <= 9 ))
            return true;
        if (input != ':')
            return true;
    }

    return false;
}
*/
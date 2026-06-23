// Previously I had to do:
// Library for excell/libreoffice
//
// sudo apt update
// sudo apt install libxlsxwriter-dev
// check:
// dpkg -l | grep xlsxwriter
// Compilation: 
// g++ excel_output_experimental.cpp -o excel_output -lxlsxwriter

#include <xlsxwriter.h>

int main() {

    lxw_workbook* workbook = workbook_new("report.xlsx");
    lxw_worksheet* sheet = workbook_add_worksheet(workbook, "Results");

    // Header format
    lxw_format* header = workbook_add_format(workbook);
    format_set_bold(header);
    format_set_bg_color(header, 0xD9EAF7);      // soft blue

    // Soft green
    lxw_format* pass_fmt = workbook_add_format(workbook);
    format_set_bg_color(pass_fmt, 0xDFF0D8);

    // Soft red
    lxw_format* fail_fmt = workbook_add_format(workbook);
    format_set_bg_color(fail_fmt, 0xF2DEDE);

    // Soft yellow
    lxw_format* review_fmt = workbook_add_format(workbook);
    format_set_bg_color(review_fmt, 0xFCF8E3);

    // Orange text
    lxw_format* orange_text = workbook_add_format(workbook);
    format_set_font_color(orange_text, 0xE67E22);
    format_set_bold(orange_text);

    // Headers
    worksheet_write_string(sheet, 0, 0, "Name", header);
    worksheet_write_string(sheet, 0, 1, "Score", header);
    worksheet_write_string(sheet, 0, 2, "Status", header);
    worksheet_write_string(sheet, 0, 3, "Colour", header);

    // Alice
    worksheet_write_string(sheet, 1, 0, "Alice", NULL);
    worksheet_write_number(sheet, 1, 1, 95, pass_fmt);
    worksheet_write_string(sheet, 1, 2, "PASS", pass_fmt);
    worksheet_write_string(sheet, 1, 3, "Soft Green", orange_text);

    // Bob
    worksheet_write_string(sheet, 2, 0, "Bob", NULL);
    worksheet_write_number(sheet, 2, 1, 45, fail_fmt);
    worksheet_write_string(sheet, 2, 2, "FAIL", fail_fmt);
    worksheet_write_string(sheet, 2, 3, "Soft Red", orange_text);

    // Charlie
    worksheet_write_string(sheet, 3, 0, "Charlie", NULL);
    worksheet_write_number(sheet, 3, 1, 70, review_fmt);
    worksheet_write_string(sheet, 3, 2, "REVIEW", review_fmt);
    worksheet_write_string(sheet, 3, 3, "Soft Yellow", orange_text);

    worksheet_set_column(sheet, 0, 3, 20, NULL);

    workbook_close(workbook);

    return 0;
}
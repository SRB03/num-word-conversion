#include <stdio.h>
#include <stdlib.h>

/*
 A simple CLI program to calculate income tax under India's
 old and new tax regimes (assumptions below). The program:
 - Prompts for annual gross salary (INR)
 - Prompts for total deductions allowed under the OLD regime (INR)
 - Applies a standard deduction of 50,000 for the OLD regime (assumes salaried)
 - Calculates tax according to common slabs and adds 4% cess

 Assumptions / notes:
 - Uses common Indian slabs: old-regime (0/5/20/30) and new-regime (0/5/10/15/20/25/30)
 - Applies rebate (section 87A style) to reduce tax to zero for taxable income up to 500,000
 - Does NOT compute surcharge or individual exemptions other than the standard deduction
 - Currencies are INR; inputs may be decimal numbers
*/

double calc_tax_old(double taxable);

double calc_tax_new(double taxable);

int main(void) {
    double salary = 0.0;
    double old_deductions = 0.0;
    const double standard_deduction = 50000.0; /* assumed for salaried person */

    printf("\tIncome Tax Calculator (CLI)\n");
    printf("---------------------------------------------\n");
    printf("Enter annual gross salary (INR): ");
    if (scanf("%lf", &salary) != 1) {
        fprintf(stderr, "Invalid salary input. Exiting.\n");
        return 1;
    }

    if (salary < 0) {
        fprintf(stderr, "Salary cannot be negative. Exiting.\n");
        return 1;
    }

    printf("Enter total deductions allowed under OLD regime (INR, excluding standard deduction). If none, enter 0: ");
    if (scanf("%lf", &old_deductions) != 1) {
        fprintf(stderr, "Invalid deductions input. Exiting.\n");
        return 1;
    }

    if (old_deductions < 0) old_deductions = 0.0;

    /* OLD regime taxable income: salary - standard deduction - old_deductions */
    double taxable_old = salary - standard_deduction - old_deductions;
    if (taxable_old < 0.0) taxable_old = 0.0;

    /* NEW regime taxable income: salary (no standard deduction/exemptions assumed) */
    double taxable_new = salary;

    double tax_old = calc_tax_old(taxable_old);
    double tax_new = calc_tax_new(taxable_new);

    printf("\nResults:\n");
    printf("---------------------------------------------\n");
    printf("OLD REGIME:\n");
    printf("  Gross salary:       \t%.2f\n", salary);
    printf("  Standard deduction: \t%.2f\n", standard_deduction);
    printf("  Other deductions:   \t%.2f\n", old_deductions);
    printf("  Taxable income:     \t%.2f\n", taxable_old);
    printf("  Income tax (incl. 4%% cess): \t%.2f\n", tax_old);
    printf("  Effective tax rate: \t%.2f%%\n", (salary > 0.0) ? (tax_old / salary * 100.0) : 0.0);
    printf("\nNEW REGIME:\n");
    printf("  Taxable income:     \t%.2f\n", taxable_new);
    printf("  Income tax (incl. 4%% cess): \t%.2f\n", tax_new);
    printf("  Effective tax rate: \t%.2f%%\n", (salary > 0.0) ? (tax_new / salary * 100.0) : 0.0);
    printf("---------------------------------------------\n");

    if (tax_old < tax_new) {
        printf("Recommendation: OLD regime is cheaper by %.2f INR.\n", tax_new - tax_old);
    } else if (tax_new < tax_old) {
        printf("Recommendation: NEW regime is cheaper by %.2f INR.\n", tax_old - tax_new);
    } else {
        printf("Recommendation: Both regimes result in the same tax.\n");
    }

    return 0;
}
double calc_tax_old(double taxable) {
    if (taxable <= 0) return 0.0;
    double tax = 0.0;

    if (taxable <= 250000.0) {
        tax = 0.0;
    } else if (taxable <= 500000.0) {
        tax = (taxable - 250000.0) * 0.05;
    } else if (taxable <= 1000000.0) {
        tax = (250000.0) * 0.05 + (taxable - 500000.0) * 0.20;
    } else {
        tax = (250000.0) * 0.05 + (500000.0) * 0.20 + (taxable - 1000000.0) * 0.30;
    }

    /* Rebate (section 87A style): taxable up to 5,00,000 -> tax reduced up to 12,500 */
    if (taxable <= 500000.0) {
        if (tax <= 12500.0) tax = 0.0; else tax -= 12500.0;
    }

    /* Health & Education Cess 4% */
    tax += tax * 0.04;
    return tax;
}
double calc_tax_new(double taxable) {
    if (taxable <= 0) return 0.0;
    double tax = 0.0;

    if (taxable <= 250000.0) {
        tax = 0.0;
    } else if (taxable <= 500000.0) {
        tax = (taxable - 250000.0) * 0.05;
    } else if (taxable <= 750000.0) {
        tax = (250000.0) * 0.05 + (taxable - 500000.0) * 0.10;
    } else if (taxable <= 1000000.0) {
        tax = (250000.0) * 0.05 + (250000.0) * 0.10 + (taxable - 750000.0) * 0.15;
    } else if (taxable <= 1250000.0) {
        tax = (250000.0) * 0.05 + (250000.0) * 0.10 + (250000.0) * 0.15 + (taxable - 1000000.0) * 0.20;
    } else if (taxable <= 1500000.0) {
        tax = (250000.0) * 0.05 + (250000.0) * 0.10 + (250000.0) * 0.15 + (250000.0) * 0.20 + (taxable - 1250000.0) * 0.25;
    } else {
        tax = (250000.0) * 0.05 + (250000.0) * 0.10 + (250000.0) * 0.15 + (250000.0) * 0.20 + (250000.0) * 0.25 + (taxable - 1500000.0) * 0.30;
    }

    /* Rebate like old regime for incomes up to 5,00,000 */
    if (taxable <= 500000.0) {
        if (tax <= 12500.0) tax = 0.0; else tax -= 12500.0;
    }

    tax += tax * 0.04; /* cess */
    return tax;
}
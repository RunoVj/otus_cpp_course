//
// Created by RunoVj on 5/28/2022.
//
#pragma once

long factorial(const int n)
{
    long f = 1;
    for (int i = 1; i <= n; ++i) {
        f *= i;
    }
    return f;
}

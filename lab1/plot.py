import pandas as pd
import matplotlib.pyplot as plt
import os

df = pd.read_csv(
    r"C:\Users\evgen\Evgeny\Dev_projects\Dev_CPP\Analysis_of_algorithms\cmake-build-debug\sorting_times.csv")
output_dir = r"C:\Users\evgen\Evgeny\Dev_projects\Dev_CPP\Analysis_of_algorithms\lab1\images"

cases = ["Random", "Best", "Worst"]
for case in cases:
    df_case = df[df["Case"] == case]

    plt.figure(figsize=(8, 5))
    plt.plot(df_case["Size"], df_case["BubbleSort"], marker='o', label="BubbleSort")
    plt.plot(df_case["Size"], df_case["InsertionSort"], marker='s', label="InsertionSort")
    plt.plot(df_case["Size"], df_case["ShellSort"], marker='^', label="ShellSort")

    plt.xlabel("Размер массива")
    plt.ylabel("Процессорное время (сек)")
    plt.title(f"Трудоемкость {case}")
    plt.legend()
    plt.grid()
    plt.savefig(os.path.join(output_dir, f"sorting_{case}.png"))
    plt.show()

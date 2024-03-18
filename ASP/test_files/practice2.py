import time

import pandas as pd

import practice1

def calculate_avg():
    start = time.time()
    table = pd.read_csv('../diabetes_data_upload.csv')
    print(table)
    end = time.time()
    return end-start


def calculate_avg_with_group_by():
    start = time.time()
    table = pd.read_csv('../diabetes_data_upload.csv')
    print(table.groupby('Gender')['Age'].mean())
    end = time.time()
    return end - start


times_avg = calculate_avg()
times_avg_with_group_by = calculate_avg_with_group_by()
times_practice1 = []

start = time.time()
data = practice1.read_file()
practice1.calculate_avg(data)
end = time.time()
times_practice1.append(end-start)

start = time.time()
data = practice1.read_file()
practice1.calculate_avg_group_by(data)
end = time.time()
times_practice1.append(end-start)

print(f'(Age) time practice1: {times_practice1[0]}; time practice2: {times_avg}')
print(f'(Group by gender) time practice1: {times_practice1[1]}; time practice2: {times_avg_with_group_by}')
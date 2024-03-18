import numpy as np
import pandas as pd


def get_uniform_and_normally_distributed_numbers():
    array_numbers = np.array([1, 2, 3, 4, 5, 6, 7])
    print(array_numbers)
    array_numbers = np.random.rand(7)
    print('uniform  distributed numbers ', array_numbers)
    array_numbers = np.random.randn(7)
    print('normally distributed numbers ', array_numbers)
    array_numbers = np.array([1, 2, 3, 4, 5, 6, 7])
    print('Length array ', array_numbers.shape)
    print('number of axes ', array_numbers.ndim)
    print('type ', array_numbers.dtype.name)
    print('size in bytes', array_numbers.itemsize)
    print('width', array_numbers.size)


def get_avg_with_group_by():
    data = pd.read_csv('../diabetes_data_upload.csv')
    print(data.dtypes)
    data.dtypes.to_csv('../diabets_types.csv')

    data.loc[data.Gender == 'Male', 'Gender'] = 0
    data.loc[data.Gender == 'Female', 'Gender'] = 1
    data[data == 'Yes'] = 0
    data[data == 'Positive'] = 0
    data[data == 'No'] = 1
    data[data == 'Negative'] = 1
    print(data)
    data.to_csv('../diabets_data_with_classes.csv')
    print('avg age group by gender:', data.groupby('Gender')['Age'].mean())


# get_uniform_and_normally_distributed_numbers()
# get_avg_with_group_by()
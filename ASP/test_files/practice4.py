
import pandas as pd
import matplotlib.pyplot as plt

N = 11


def get_n_types_indexes_stats(data):
    print('types')
    print(data[data.columns[:5]][:N + 3].dtypes)
    print('indexes')
    print(data[data.columns[:5]][:N + 3].index)
    print('stats')
    print(data[data.columns[:5]][:N + 3].describe(include='all'))


def get_with_yes_no(data):
    print('\nwith "Yes"')
    print(data[data[data.columns[N + 2]] == 'Yes'])
    print('\nwith "No"')
    print(data[data[data.columns[N + 2]] == 'No'])


def sort_data(data):
    print('sort: ')
    print(data.sort_values(by=[data.columns[N + 1], data.columns[N + 2], 'Age']))


def delete_null_line(data):
    new_data = data
    new_data.dropna(how='any')
    print('Удаляем строки с пустотой')
    print(new_data)


def get_hist(data):
    data_yes = data[data[data.columns[N + 2]] == 'Yes']
    data_no = data[data[data.columns[N + 2]] == 'No']
    plt.figure(1)
    plt.subplot(121)
    plt.hist(data_yes.iloc[:, 0], color="r")
    plt.title(f"hist with {data.columns[N + 2]}")
    plt.xlabel("age")
    plt.ylabel("count")
    plt.subplot(122)
    plt.title(f"hist without {data.columns[N + 2]}")
    plt.hist(data_no.iloc[:, 0], color="b")
    plt.xlabel("age")
    plt.ylabel("count")
    plt.show()


def get_boxplot(data):
    data_yes = data[data[data.columns[N + 2]] == 'Yes']
    data_no = data[data[data.columns[N + 2]] == 'No']
    plt.figure(1)
    plt.subplot(211)
    plt.boxplot(data_yes.iloc[:, 0], vert=False)
    plt.xlabel("age")
    plt.subplot(212)
    plt.boxplot(data_no.iloc[:, 0], vert=False)
    plt.xlabel("age")
    plt.show()


def get_scatter_matrix():
    data_with_classes = pd.read_csv('../diabets_data_with_classes.csv')
    sorted_data = data_with_classes.iloc[:, [1, N + 2, N + 3]]
    # вот тут запомни что не понял нах тебе класс(столбец с таким названием) если его в данных нет так как рассматриваются другие столбцы
    pd.plotting.scatter_matrix(sorted_data, c=sorted_data[sorted_data.columns[-1]].replace(["0", "1"], ["blue", "red"]))
    plt.show()


data = pd.read_csv('../diabetes_data_upload.csv')
get_n_types_indexes_stats(data)
# get_with_yes_no(data)
# sort_data(data)
# delete_null_line(data)
# get_hist(data)
# get_boxplot(data)
# get_scatter_matrix()

import csv


def read_file():
    with open('../diabetes_data_upload.csv', newline='') as file:
        data = list(csv.reader(file))
    print(data)
    return data


def calculate_avg(data):
    sum_num = 0
    nums = data[1:]
    for i in nums:
        sum_num += int(i[0])
    avg = sum_num / len(nums)
    print(avg)


def calculate_avg_group_by(data):
    avg_male = 0
    avg_female = 0
    elements = data[1:]
    for element in elements:
        if element[1] == 'Male':
            avg_male += int(element[0])
        elif element[1] == 'Female':
            avg_female += int(element[0])
    avg_male /= len(elements)
    avg_female /= len(elements)
    print(avg_male)
    print(avg_female)


def get_indexes_groups(data):
    elements = data[1:]
    yes_yes = []
    yes_no = []
    no_yes = []
    no_no = []
    for i in range(len(elements)):
        if elements[i][-1] == 'Positive':
            if elements[i][-2] == 'No':
                yes_no.append(i + 1)
            elif elements[i][-2] == 'Yes':
                yes_yes.append(i + 1)
        elif elements[i][-1] == 'Negative':
            if elements[i][-2] == 'No':
                no_no.append(i + 1)
            elif elements[i][-2] == 'Yes':
                no_yes.append(i + 1)

    print(f'Positive Positive: {yes_yes}\n')
    print(f'Positive Negative: {yes_no}\n')
    print(f'Negative Positive: {no_yes}\n')
    print(f'Negative Negative: {no_no}\n')


# data = read_file()
# calculate_avg(data)
# calculate_avg_group_by(data)
# get_indexes_groups(data)
import csv


def part1():
    with open('./python/diabetes_data_upload.csv') as file:
        data = list(csv.reader(file))
    print(data)
    return data

def part2(data):
    summ = 0
    nums = data[1:]
    for i in nums:
        summ += int(i[0])
    avg = summ / len(nums)
    print(avg)

def part3(data):
    avgMale = 0
    avgFemale = 0
    nums = data[1:]
    for i in nums:
        if i[1] == 'Male':
            avgMale += int(i[0])
        elif i[1] == 'Female':
            avgFemale += int(i[0])
    avgMale = avgMale / len(nums)
    avgFemale = avgFemale / len(nums)
    print(avgMale, avgFemale)

def part4(data):
    nums = data[1:]
    pos_pos = []
    pos_neg = []
    neg_pos = []
    neg_neg = []
    for i in range(len(nums)):
        if nums[i][-1] == 'Negative':
            if nums[i][-2] == 'No':
                neg_neg.append(i + 1)
            elif nums[i][-2] == 'Yes':
                neg_pos.append(i + 1)
        elif nums[i][-1] == 'Positive':
            if nums[i][-2] == 'No':
                pos_neg.append(i + 1)
            elif nums[i][-2] == 'Yes':
                pos_pos.append(i + 1)
    print('Positive and positive:', pos_pos)
    print('Positive and negative:', pos_neg)
    print('Negative and positive:', neg_pos)
    print('Negative and negative:', neg_neg)

data = part1()
part2(data)
# part3(data)
# part4(data)
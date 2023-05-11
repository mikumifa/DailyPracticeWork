
score = [['Python', 89], ['Docker', 90], ['Linux', 95], ['Java', 65]]

with open('score.txt', 'w') as file:
    for item in score:
        file.write(item[0] + ' ' + str(item[1]) + '\n')

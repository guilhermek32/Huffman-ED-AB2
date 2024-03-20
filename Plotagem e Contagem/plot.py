import matplotlib
import matplotlib.pyplot as plt

matplotlib.use('TkAgg')
# Read data from file
data = []
with open('out.txt', 'r') as file:
    for line in file:
        data.append(list(map(int, line.strip().split(' '))))

# Extract x and y values
x1 = [entry[0] for entry in data]
y1 = [entry[1] for entry in data]
y2 = [entry[2] for entry in data]

# Plot the data
plt.plot(x1, y1, label='Lista (random)', color='blue', linestyle='dotted')
plt.plot(x1, y2, label='Árvore de busca binária', color='red', linestyle='dotted')

# Customize the plot
plt.xlabel('Tamanho (n)')
plt.ylabel('comparações')
plt.title('Contagem e plotagem entre lista e Árvore de busca binária')
plt.legend('-')

# new plot with the same data
plt.figure()
plt.plot(x1, y2, label='Árvore de busca binária', color='red', linestyle='dotted')
plt.xlabel('Tamanho (n)')
plt.ylabel('comparações')
plt.title('Árvore de Busca Binária')




# Show the plot
plt.show()
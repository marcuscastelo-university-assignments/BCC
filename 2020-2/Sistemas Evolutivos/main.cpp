#include <iostream>
#include <GL/glut.h>
#include <vector>
#include <exception>
#include "graphing.h"
#include <math.h>

#define POPULATION_SIZE 10
#define PLOT_DELTA_X 1

#define GRAPH_START_X 0
#define GRAPH_END_X 3000

#define MUTATION_BASE_PERC 3

float sigmoid(float x) {
    return 30 * (1 / (1 + exp( - (x-33.67) / 10 ) ));
}

struct Individual {
    float x;
};

std::vector<Individual> g_population;
std::vector<Individual>::iterator g_bestIndividualIt;
int g_best_fitness = -1;
int g_stagnation_counter = 0;

void updateBestIndividual();
void initPopulation() {
    for (size_t i = 0; i < POPULATION_SIZE; i++)
        g_population.push_back({ 1+0*(float)(rand() % (GRAPH_END_X - GRAPH_START_X)) + GRAPH_START_X });
    updateBestIndividual();
}

float calcFuncValue(float x) {
    return graphing::plot(x);
}

float calcFitness(const Individual& individual) {
    if (individual.x > GRAPH_END_X || individual.x < GRAPH_START_X) throw std::runtime_error("x fora do gráfico");
    return calcFuncValue(individual.x);
}

void updateBestIndividual() {
    auto lastBestIt = g_bestIndividualIt;
    g_bestIndividualIt = g_population.begin();
    float bestFitness = calcFitness(*g_bestIndividualIt);
    for (auto currIndivIt = g_bestIndividualIt + 1; currIndivIt != g_population.end(); currIndivIt++) {
        float currFitness = calcFitness(*currIndivIt);
        if (currFitness > bestFitness) {
            g_bestIndividualIt = currIndivIt;
            bestFitness = currFitness;
        }
    }
}

Individual crosOver(const Individual& mother, const Individual& father) {
    return (Individual){ (mother.x + father.x) / 2 };
}

void crossOverInPlace(Individual& receiver, const Individual& donator) {
    receiver.x = (receiver.x + donator.x) / 2.0f;
}

float calcMutationPercentage() {
    return sigmoid(g_stagnation_counter) * MUTATION_BASE_PERC;
}

float calcRandomizedMutationPercentage() {
    float randomizer = ((rand() % 2000) - 1000) / 1000.f;
    return calcMutationPercentage() * randomizer;
}

void mutateInPlace(Individual& target) {
    float mutation_absolute = (calcRandomizedMutationPercentage()/100.f) * (GRAPH_END_X - GRAPH_START_X);

    target.x += mutation_absolute;
    if (target.x < GRAPH_START_X) target.x = GRAPH_START_X;
    else if (target.x > GRAPH_END_X) target.x = GRAPH_END_X;
}

void elitism() {
    for (auto currIndivIt = g_population.begin(); currIndivIt != g_population.end(); currIndivIt++) {
        if (currIndivIt == g_bestIndividualIt) continue;
        crossOverInPlace(*currIndivIt, *g_bestIndividualIt);
    }
}


//TODO: fix. This is probably not working
void tournament() {
    int vector_start = rand() % POPULATION_SIZE;

    std::vector<int> father_winners, mother_winners;
    for (int i = 0; i < POPULATION_SIZE/2; i++)
    {
        int a = (vector_start + i) % POPULATION_SIZE,
            b = (vector_start + POPULATION_SIZE - 1 - i) % POPULATION_SIZE;
        if (calcFitness(g_population[a]) >= calcFitness(g_population[b])) {
            father_winners.push_back(a);
        } else {
            father_winners.push_back(b);
        }
    }

    for (int i = 0; i < POPULATION_SIZE/2; i++)
    {
        int a = (vector_start + i) % POPULATION_SIZE,
            b = (vector_start + POPULATION_SIZE/2 + i) % POPULATION_SIZE;
        if (calcFitness(g_population[a]) >= calcFitness(g_population[b])) {
            mother_winners.push_back(a);
        } else {
            mother_winners.push_back(b);
        }
    }

    if (mother_winners.size() != father_winners.size()) {
        std::cout << "ERROR: INVALID STATE MOTHER VS FATHER" << std::endl;
        throw std::logic_error("ERROR: INVALID STATE MOTHER VS FATHER");
    }
    
    std::vector<Individual> new_population;
    new_population.reserve(POPULATION_SIZE);
    //Keeps best individual alive
    new_population.push_back(*g_bestIndividualIt);
    g_bestIndividualIt = g_population.begin();

    if (mother_winners.size() > 1) 
        new_population.push_back((g_population[mother_winners[0]], g_population[father_winners[0]]));

    for (int i = 2; i < mother_winners.size(); i++)
    {
        new_population.push_back((g_population[mother_winners[i]], g_population[*(father_winners.rbegin()+i)]));
        new_population.push_back((g_population[mother_winners[i]], g_population[father_winners[i]]));
    }

    g_population = new_population;
}

void mutateAllExceptBest() {
    for (auto currIndivIt = g_population.begin(); currIndivIt != g_population.end(); currIndivIt++) {
        if (currIndivIt == g_bestIndividualIt) continue;
        mutateInPlace(*currIndivIt);
    }
}

void updateStagnation() {
    //if current fitness is better than last
    int bestindfit = calcFitness(*g_bestIndividualIt);
    if (bestindfit > g_best_fitness) {
        g_best_fitness = bestindfit;
        g_stagnation_counter = 0;
    } else g_stagnation_counter++;
}

void stepGeneration() {
    //Availate current generation
    updateBestIndividual();
    updateStagnation();

    //Generate new generation
    elitism(); // tournament();
    mutateAllExceptBest();
}

void drawIndividual(const Individual& individual) {
    float x = individual.x;
    float y = calcFitness(individual);

    if (g_bestIndividualIt->x == individual.x) 
        glColor3f(1.f, 0.f, 0.f);
    else 
        glColor3f(0.f, 1.f, 0.f);

    glPointSize(10.f);
    glBegin(GL_POINTS);
        glVertex2f(x, y);
    glEnd();
}

void drawPopulation() {
    static int generation = 1;
    std::cout << "Generation " << generation++ << " [ stagnated for " << g_stagnation_counter << " gens, mutation is " << calcMutationPercentage() << "% ]" << std::endl;

    int ind = 1;
    for (auto indivIt = g_population.begin(); indivIt != g_population.end(); indivIt++) {
        if (indivIt == g_bestIndividualIt) std::cout << "\033[1;31m";
        std::cout << "Individual " << ind++ <<  ": x = " << indivIt->x << ", fit = " << calcFitness(*indivIt) << "\033[0m" << std::endl;
        drawIndividual(*indivIt);
    }
}

void plotFunc() {
    int y;

    glPointSize(5.f);
    glLineWidth(5.f);
    glColor3f(0.f,0.f,1.f);
    glBegin(GL_POINTS);

        for (int x = GRAPH_START_X; x <= GRAPH_END_X; x+=PLOT_DELTA_X)
        {
            y = calcFuncValue(x);
            glVertex2f(x,y);
        }
    
    glEnd();
}

void drawWindow() {
    glClearColor(.0f,.0f,.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    plotFunc();
    drawPopulation();

    glFlush();
}

void handleKeyPress(unsigned char key, int x, int y) {
    if (key == 13) {
        for (size_t i = 0; i < 1; i++)
        {
            stepGeneration();
            glutPostRedisplay();
        }
    }
}

int main(int argc, char const *argv[])
{
    srand(413);
    
    glutInit(&argc, (char**) argv);
    glutInitWindowPosition(558, 240);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Teste");

    gluOrtho2D(GRAPH_START_X, GRAPH_END_X, 0, 1000);
    
    glutDisplayFunc(drawWindow);
    glutKeyboardFunc(handleKeyPress);

    initPopulation();

    glutMainLoop();
    return 0;
}

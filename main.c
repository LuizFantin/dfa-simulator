#include<stdio.h>
#include<string.h>


// Check if the element is in array
int isInArray(char element, char* array){
    for (int i = 0; i < strlen(array); i++)
        if(array[i] == element)
            return 1;
    return 0;
}


// Find the specific transition through the initial state and the action
int findTransition(char fromState, char action, int numberTransations, char transations[][3]){
    for (int i = 0; i < numberTransations; i++)
    {
        if((fromState == transations[i][0]) && (action == transations[i][1]))
            return i;
    }
    return -1;
}

int main(){
    int numberStates;
    int numberActions;
    int numberInitialStates;
    int numberFinalStates;
    int numberTransitions;
    int numberInputStrings;
    char currentState;
    int acceptLambda = 0;

    // Line 1
    scanf("%d", &numberStates);

    // Line 2
    scanf("%d", &numberActions);
    char actions[numberActions];
    for (int i = 0; i < numberActions; i++)
    {
        scanf(" %c", &actions[i]);
    }
 
    // Line 3
    scanf("%d", &numberInitialStates);

    // Line 4
    scanf("%d", &numberFinalStates);
    char finalStates[numberFinalStates];
    for (int i = 0; i < numberFinalStates; i++)
    {
        scanf(" %c", &finalStates[i]);
        if(finalStates[i] == '0')
            acceptLambda = 1;
    }

    // Line 5
    scanf("%d", &numberTransitions);
    int numberStepsTransitions = 3;
    char transitions[numberTransitions][numberStepsTransitions];
    for (int i = 0; i < numberTransitions; i++) // ex: 0a1 0a2
    {
        scanf(" %c", &transitions[i][0]); // from
        scanf(" %c", &transitions[i][1]); // pass
        scanf(" %c", &transitions[i][2]); // to
        fflush(stdin);
    }
    

    // Inputs for tests
    scanf("%d", &numberInputStrings);
    char inputStrings[numberInputStrings][21];
    for (int i = 0; i < numberInputStrings; i++)
    {
        scanf("%s", inputStrings[i]);
    }

    char output[numberInputStrings][21];

    for(int i = 0; i < numberInputStrings; i++){
        // It always starts at state '0';
        currentState = '0';

        // Checks if test input string is lambda, ie '-' 
        if(strcmp(inputStrings[i], "-") == 0){
            if(acceptLambda == 1)
                strcpy(output[i], "aceita");
            else
                strcpy(output[i], "rejeita");
        }
        else{
            // Runs through the input string
            for (int j = 0; inputStrings[i][j] != '\0'; j++)
            {
                // Checks if the action present in the input string is contained in the allowed actions 
                if(isInArray(inputStrings[i][j], actions) == 0){
                    strcpy(output[i], "rejeita");
                    break;
                }

                // Finds the position of the transition.
                int positionOfTransition = findTransition(currentState, inputStrings[i][j], numberTransitions, transitions);

                // Set new current state to the final state presents in the trasitions sought after
                currentState = transitions[positionOfTransition][2];

               // Checks if the current state is a final state and if it is at the end of the input string 
                if(isInArray(currentState, finalStates) && inputStrings[i][j+1] == '\0')
                    strcpy(output[i], "aceita");
                else
                    strcpy(output[i], "rejeita");
            }
        }

        printf("%s\n", output[i]);
    }
    return 0;
}


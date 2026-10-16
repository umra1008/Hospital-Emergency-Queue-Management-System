/*
 * Hospital Emergency Queue Management System
 * Academic DSA project in C
 *
 * Features:
 *  - Register a patient
 *  - Assign emergency priority (1 = Critical, 2 = Serious, 3 = Normal)
 *  - Display waiting patients
 *  - Serve the highest-priority patient
 *  - Search for a patient by ID
 *  - Show queue statistics
 *
 * Note: This is an educational demonstration, not a clinical triage tool.
 */

#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 100
#define NAME_LENGTH 50
#define CONDITION_LENGTH 100

typedef struct {
    int id;
    char name[NAME_LENGTH];
    int age;
    char condition[CONDITION_LENGTH];
    int priority;
    unsigned long arrivalOrder;
} Patient;

Patient queue[MAX_PATIENTS];
int patientCount = 0;
int nextPatientId = 1;
unsigned long nextArrivalOrder = 1;

void clearInputBuffer(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        /* Discard remaining input */
    }
}

int readInt(const char *prompt, int minValue, int maxValue) {
    int value;
    int result;

    while (1) {
        printf("%s", prompt);
        result = scanf("%d", &value);

        if (result == 1 && value >= minValue && value <= maxValue) {
            clearInputBuffer();
            return value;
        }

        printf("Invalid input. Enter a number between %d and %d.\n",
               minValue, maxValue);
        clearInputBuffer();
    }
}

void readLine(const char *prompt, char *buffer, size_t size) {
    size_t length;

    printf("%s", prompt);
    if (fgets(buffer, (int)size, stdin) == NULL) {
        buffer[0] = '\0';
        return;
    }

    length = strlen(buffer);
    if (length > 0 && buffer[length - 1] == '\n') {
        buffer[length - 1] = '\0';
    } else {
        clearInputBuffer();
    }
}

const char *priorityName(int priority) {
    switch (priority) {
        case 1: return "Critical";
        case 2: return "Serious";
        case 3: return "Normal";
        default: return "Unknown";
    }
}

/* Lower priority number means greater urgency.
   For equal priorities, the patient who arrived first is served first. */
int comesBefore(const Patient *a, const Patient *b) {
    if (a->priority != b->priority) {
        return a->priority < b->priority;
    }
    return a->arrivalOrder < b->arrivalOrder;
}

void registerPatient(void) {
    Patient p;
    int i;

    if (patientCount >= MAX_PATIENTS) {
        printf("\nQueue is full. Cannot register more patients.\n");
        return;
    }

    p.id = nextPatientId++;
    readLine("Enter patient name: ", p.name, sizeof(p.name));

    if (p.name[0] == '\0') {
        printf("Name cannot be empty. Registration cancelled.\n");
        nextPatientId--;
        return;
    }

    p.age = readInt("Enter patient age (0-120): ", 0, 120);
    readLine("Enter brief condition/reason for visit: ",
             p.condition, sizeof(p.condition));

    printf("\nPriority levels:\n");
    printf("1. Critical\n2. Serious\n3. Normal\n");
    p.priority = readInt("Select priority (1-3): ", 1, 3);
    p.arrivalOrder = nextArrivalOrder++;

    /* Insert in priority order while preserving arrival order for ties. */
    i = patientCount;
    while (i > 0 && comesBefore(&p, &queue[i - 1])) {
        queue[i] = queue[i - 1];
        i--;
    }
    queue[i] = p;
    patientCount++;

    printf("\nPatient registered successfully.\n");
    printf("Patient ID: %d\n", p.id);
    printf("Assigned priority: %s\n", priorityName(p.priority));
}

void displayPatients(void) {
    int i;

    if (patientCount == 0) {
        printf("\nNo patients are currently waiting.\n");
        return;
    }

    printf("\n================ WAITING PATIENTS ================\n");
    printf("%-6s %-20s %-5s %-12s %-30s\n",
           "ID", "Name", "Age", "Priority", "Condition");
    printf("--------------------------------------------------------------------------\n");

    for (i = 0; i < patientCount; i++) {
        printf("%-6d %-20.20s %-5d %-12s %-30.30s\n",
               queue[i].id,
               queue[i].name,
               queue[i].age,
               priorityName(queue[i].priority),
               queue[i].condition);
    }
}

void serveNextPatient(void) {
    int i;
    Patient served;

    if (patientCount == 0) {
        printf("\nNo patients are waiting to be served.\n");
        return;
    }

    served = queue[0];

    printf("\nNext patient served:\n");
    printf("Patient ID : %d\n", served.id);
    printf("Name       : %s\n", served.name);
    printf("Age        : %d\n", served.age);
    printf("Priority   : %s\n", priorityName(served.priority));
    printf("Condition  : %s\n", served.condition);

    for (i = 1; i < patientCount; i++) {
        queue[i - 1] = queue[i];
    }
    patientCount--;

    printf("\nPatient removed from the waiting queue.\n");
}

void searchPatient(void) {
    int id;
    int i;

    if (patientCount == 0) {
        printf("\nThe waiting queue is empty.\n");
        return;
    }

    id = readInt("Enter patient ID to search: ", 1, 1000000000);

    for (i = 0; i < patientCount; i++) {
        if (queue[i].id == id) {
            printf("\nPatient found:\n");
            printf("Patient ID : %d\n", queue[i].id);
            printf("Name       : %s\n", queue[i].name);
            printf("Age        : %d\n", queue[i].age);
            printf("Condition  : %s\n", queue[i].condition);
            printf("Priority   : %s\n", priorityName(queue[i].priority));
            printf("Queue position: %d\n", i + 1);
            return;
        }
    }

    printf("\nNo waiting patient found with ID %d.\n", id);
    printf("The patient may already have been served.\n");
}

void showStatistics(void) {
    int i;
    int critical = 0;
    int serious = 0;
    int normal = 0;

    for (i = 0; i < patientCount; i++) {
        if (queue[i].priority == 1) {
            critical++;
        } else if (queue[i].priority == 2) {
            serious++;
        } else if (queue[i].priority == 3) {
            normal++;
        }
    }

    printf("\n=========== QUEUE STATISTICS ===========\n");
    printf("Total waiting patients : %d\n", patientCount);
    printf("Critical patients      : %d\n", critical);
    printf("Serious patients       : %d\n", serious);
    printf("Normal patients        : %d\n", normal);
    printf("Available queue spaces : %d\n", MAX_PATIENTS - patientCount);
}

void showMenu(void) {
    printf("\n============================================\n");
    printf(" HOSPITAL EMERGENCY QUEUE MANAGEMENT SYSTEM\n");
    printf("============================================\n");
    printf("1. Register Patient\n");
    printf("2. Display Waiting Patients\n");
    printf("3. Serve Next Patient\n");
    printf("4. Search Patient by ID\n");
    printf("5. Show Queue Statistics\n");
    printf("6. Exit\n");
}

int main(void) {
    int choice;

    printf("Welcome to the Hospital Emergency Queue Management System\n");

    do {
        showMenu();
        choice = readInt("Enter your choice (1-6): ", 1, 6);

        switch (choice) {
            case 1:
                registerPatient();
                break;
            case 2:
                displayPatients();
                break;
            case 3:
                serveNextPatient();
                break;
            case 4:
                searchPatient();
                break;
            case 5:
                showStatistics();
                break;
            case 6:
                printf("\nThank you for using the system. Goodbye!\n");
                break;
            default:
                /* readInt limits the choice to 1-6 */
                break;
        }
    } while (choice != 6);

    return 0;
}

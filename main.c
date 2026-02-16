// Space Pirates

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//#define USER_SEED // Let the user decide the seed.

unsigned char qx;
unsigned char qy;
unsigned char sx;
unsigned char sy;

int energy;
int sheild;
int torpedos;
int credits;

int qseeds[12][12];
unsigned short qexist[12][12];
unsigned char smap[12][12][4];

// Space pirates main file.

// Utility functions

int len(char string[]) {
    int length = 0;
    while (string[length] != "\0") {
        length++;
    }
    return length;
}

// Standard gameplay functions

void genobjects(char work[], char fail[], short len, short bits) {
    // Generate a spesific type of object in the sector.
    short locs[len][2]; // Locations

    // Generate locations
    for (int i=0; i < len; i++) {
        locs[i][0] = rand() % 12; // X
        locs[i][1] = rand() % 12; // Y
    }

    // Verify existance, and place objects
    for (int i=0; i < len; i++) {
        if ((bits >> i) & 1) { // If the object exists
            strcpy(smap[locs[i][0]][locs[i][1]], work); // Place the object
        } else {
            strcpy(smap[locs[i][0]][locs[i][1]], fail); // Place the failed object
        }
    }

    return;
}


void visualsect() {
    // Setup seed
    int backupseed = rand(); // New seed for after
    srand(qseeds[qx][qy]);

    // Clear sector
    for (int i=0; i < 12; i++) {
        for (int j=0; j < 12; j++) {
            strcpy(smap[i][j], " . "); // Empty
        }
    }

    // Generate objects
    genobjects(" + ", " . ", 2, qexist[qx][qy] >> 14); // Stars
    genobjects("<O>", " . ", 2, qexist[qx][qy] >> 12); // Bases
    genobjects(" @ ", " . ", 4, qexist[qx][qy] >> 8); // Planets (Temp object for now)
    genobjects(" * ", " , ", 6, qexist[qx][qy]); // Asteroids

    // Place player
    strcpy(smap[sx][sy], "YOU");

    // Reset seed
    srand(backupseed);

    return;
}

void init() {
#ifndef USER_SEED
    srand(time(NULL)); // Initalize rand()
#endif

    // Setup standard variables

    int energy = 1024; // Energy
    int sheild = 1024; // Sheild energy
    int torpedos = 10; // Torpedos
    
    printf(".");

    // Setup quadrant and player location

    for (int i=0; i < 11; i++) {
        for (int j=0; j < 11; j++) {
            qseeds[i][j] = rand(); // Set the seed for this sector
            qexist[i][j] = rand() & 65535; // Set the object existance bits for this sector
        }
    }

    qx = rand() % 12; qy = rand() % 12; // Set the player in a random sector
    sx = rand() % 12; sy = rand() % 12; // Set the player in a random spot in sector

    visualsect(); // "visualize" the sector

    printf(".");
}

struct loc {
    char x;
    char y;
};

struct loc getcords(char input[]) {
    int amount = len(input)-1; // Get length
    
    char num[] = ""; // Init num[] and y vars
    char y = '0';
    
    for (int i = 0; i<amount;i++) {
        strcat(num, input[i]); // Add all except the last character
    }
    
    y = input[amount+1]-'A'; // Turn last character into cord for y

    char x = '0';

    // Package it up nicely, and ship
    struct loc output;
    output.x = 0;
}


/*
Location : Q4G.2F
Energy   : 1024
Sheild   : 1024
Torpedos : 10
Credits  : 0
*/

void print_details() {
    // Print location
    printf("\nLocation : Q%d%c.%d%c\n", qx, 'A' + qy, sx, 'A' + sy);

    // Print out other stuff
    printf("Energy   : %d\nSheild   : %d\nTorpedos : %d\nCredits  : %d\n", energy, sheild, torpedos, credits);
    return;
}

// === Commands ===

void cmd_sendhelp() {
    printf("\n just do things from superstar trek.\nIf you cant tell, this is unfinshed");
    return;
}

void cmd_nav() {
    printf("\n [insert flying stuff here]");
    return;
}

void cmd_warp() {
    printf("\n noo dont warp the wood plz");
    return;
}

void cmd_srs() {
    printf("\nShort range scan results:\nX:-A_-B_-C_-D_-E_-F_-G_-H_-I_-J_-K_-L_\n");
    for (int y=0; y<12; y++) {
        if (y > 9) {printf("%d", y);}
        if (y < 10) {printf(" "); printf("%d", y);}
        for (int x=0; x<12; x++) {
            printf(smap[x][y]);
        }
        printf("\n");//printf("\n||\n");
    }
    printf("\n");
    print_details();
    return;
}

void cmd_lrs() {
    printf("\nTo be done");
    return;
}

void endgame() {
    printf("\n*** GAME OVER ***\nCredits left: %d\n", credits);
    exit(0);
}

void cmd_end() {
    printf("\nRealy lad? You sure (Y/N)?");
    char answer[] = "is this a yes or a no";
    scanf("%s", answer);
    if (answer[0] == 'Y') {
        printf("\nWell... it was nice knowin' you capt'n - Advisor");
        endgame();
    }
    return;
}

void drink_alcohol() {
    printf("\nAfter drinking on duty, the crew deemed you too irresponsible to be the captain.");
    printf("\n\n...Now why would you go up, and do that?\n");
    // Originally, this was meant to contain quotes from people on the ship (Which were star trek characters knowing the original orgin of the game)
    // However, this is not startrek. This is space pirates. So instead, it ends like that. I do want to bring it back, but I need more characters
    // in the game for it.
    endgame();
    return;
}

// --- Commands ---

int main() {
    
    printf("\n\n\nSpace Pirates\n2026 Ominouswolf");
#ifdef USER_SEED
    printf("\nPlease enter a seed: ");
    int seed;
    scanf("%d", &seed);
    srand(seed);
    print("\nThank you!")
#endif


    printf("\nLoading");
    init();

    printf("\n");
    printf("  Welcome abord captain!\n  Say... I Haven't seen you before!\n  If ye need help, let us know!\n  Just command us with `HELP`!\n- Advisor\n");

    char cmd[] = "This is a sneaky message for those who are sneaking around the code. :)";
    char cmd_cmd[4] = "xxx"; // Get first three characters of the command
    char cmd_arg[24] = ""; // Get the right side of the command

    while (1) { // Command loop
        printf("\nYour command? ");
        scanf("%48s", cmd);
        strncpy(cmd_cmd, cmd, 3);
        strupr(cmd_cmd); // Convert it to uppercase to match original program interpretation.

        // Process command in one of the worst ways possible in my opinon.
        if (cmd[0] == 'H') {cmd_sendhelp();};
        if (strcmp(cmd_cmd, "CLS") == 0) {printf("\nno");};
        if (strcmp(cmd_cmd, "NAV") == 0) {cmd_nav();};
        if (strcmp(cmd_cmd, "WRP") == 0) {cmd_warp();};
        if (strcmp(cmd_cmd, "SRS") == 0) {cmd_srs();};
        if (strcmp(cmd_cmd, "LRS") == 0) {cmd_lrs();};
        if (strcmp(cmd_cmd, "END") == 0) {cmd_end();};
        if (strcmp(cmd_cmd, "XXX") == 0) {drink_alcohol();}; // For those who are from Super Star Trek
    }

    return 0;
}
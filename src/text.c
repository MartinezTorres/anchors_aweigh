#include <common.h>

const char * const TEXT_ANCHORS_AWEIGH[4] = { 
	"A\176\176n\176c\176h\176o\176rs A\176\176\176w\176e\176i\176g\176h\176!", 
	"L\176e\176v\176a\176n\176t\176e\176n A\176n\176c\176l\176a\176s!", 
	"L\176l\176e\176v\176e\176u\176 A\176n\176co\176r\176es!",  
	"A\176n\176k\176e\176rs W\176eg\176e\176n!", 
	};

const char * const TEXT_JOIN_THE_NAVY[4] = { "Join the Navy!", "Entra en la Marina!", "Enrola't a la Marina!", "Bij de marine gaan!" };

const char * const TEXT_FREE_PLAY[4][4] = {
	{ "Free Play (<Ensign>)", "Free Play (<Lieutenant>)", "Free Play (<Commander>)", "Free Play (<Captain>)" },
	{ "Juego Libre (<Alferez>)", "Juego Libre (<Teniente>)", "Juego Libre (<Comandante>)", "Juego Libre (<Capitan>)" },
	{ "Joc Lliure (<Alferes>)", "Joc Lliure (<Tinent>)", "Joc Lliure (<Comandant>)", "Joc Lliure (<Capita>)" },
	{ "Vrij spel (<Adelborst>)", "Vrij spel (<Luitenant>)", "Vrij spel (<Commandant>)", "Vrij spel (<Kapitein>)" } };

const char * const TEXT_INSTRUCTIONS[4] = { "Instructions", "Instrucciones", "Instruccions", "Instructies" };

const char * const TEXT_LANGUAGE[4][4] = {
	{ "Language (<American>)", "Language (<Spanish>)", "Language (<Catalan>)", "Language (<Dutch>)" },
	{ "Lenguaje (<Ingles>)", "Lenguaje (<Castellano>)", "Lenguaje (<Catalan>)", "Lenguaje (<Holandes>)" },
	{ "Llenguatge (<Angles>)", "Llenguatge (<Castella>)", "Llenguatge (<Catala>)", "Llenguatge (<Holandes>)" },
	{ "Taal (<Engels>)", "Taal (<Spaans>)", "Taal (<Catalaans>)", "Taal (<Nederlands>)" }, };


const char * const TEXT_INSTRUCTIONS_POINTER[4] = { 
	"More info at:"
	, 
	"Mas informacion en:"
	, 
	"Mes informacio a:"
	,
	"Meer info op:"
};

const char * const TEXT_WIKIPEDIA[4] = { 
	"https://en.wikipedia.org/wiki/Battleship_(puzzle)"
	, 
	"https://en.wikipedia.org/wiki/Battleship_(puzzle)"
	, 
	"https://en.wikipedia.org/wiki/Battleship_(puzzle)"
	,
	"https://nl.wikipedia.org/wiki/Zeeslag_(puzzel)"
};

const char * const TEXT_FREE_PLAY_INFO[4] = { 
	"Enjoy puzzles at the\n selected difficulty."
	, 
	"Disfruta el puzzle en la\ dificultad deseada."
	, 
	"Disfruta el puzzle en la\n dificultat desitjada."
	,
	"Geniet van puzzels met de\n geselecteerde moeilijkheidsgraad."
};

const char * const TEXT_RANKS[4][11] = {
	{ "Ensign", "Liutenant Junior", "Liutenant", "Liutenant Commander", "Commander", "Captain", "Rear Admiral", "Vice Admiral", "Admiral", "Fleet Admiral", "Admiral of the Navy" }, 
	{ "Alferez", "Teniente Junior", "Teniente", "Teniente Comandante", "Comandante", "Capitan", "Contraalmirante", "Vicealmirante", "Almirante", "Almirante General", "Almirante de la Armada" },
	{ "Alferes", "Tinent Jr.", "Tinent", "Tinent Comandant", "Comandant", "Capita", "Contraalmirall", "Vicealmirall", "Almirall", "Almirall General", "Almirall de l'Armada" },
	{ "Adelborst", "Luitenant 3e klasse","Luitenant 2e klasse", "Luitenant 1e klasse", "Kolonel", "Kapitein", "Commandeur", "Viceadmiraal", "Admiraal", "Admiraal Generaal", "Admiraal ter Vloot" } };
    
const char * const TEXT_RANKS_SHORT[4][11] = {
	{ "Ensign", "Liutenant\n Junior", "Liutenant", "Liutenant\n Commander", "Commander", "Captain", "Rear\n Admiral", "Vice\n Admiral", "Admiral", "Fleet\n Admiral", "Admiral of\n the Navy" }, 
	{ "Alferez", "Teniente\n Junior", "Teniente", "Teniente\n Comandante", "Comandante", "Capitan", "Contra\n almirante", "Vice\n almirante", "Almirante", "Almirante\n General", "Almirante de\n la Armada" },
	{ "Alferes", "Tinent Jr.", "Tinent", "Tinent\n Comandant", "Comandant", "Capita", "Contra\nalmirall", "Vice\nalmirall", "Almirall", "Almirall\n General", "Almirall de\n l'Armada" },
	{ "Adelborst", "Luitenant\n 3e klasse","Luitenant\n 2e klasse", "Luitenant\n 1e klasse", "Kolonel", "Kapitein", "Commandeur", "Viceadmiraal", "Admiraal", "Admiraal\n Generaal", "Admiraal\n ter Vloot" } };
    
const char * const TEXT_TIME_LEFT[4] = {
    "TIME LEFT:",
    "TIEMPO:",
    "TEMPS:",
    "TIJD OVER:"
};

const char * const TEXT_TIME_OVER[4] = {
    "TIME IS OVER!",
    "TIEMPO AGOTADO!",
    "TEMPS ESGOTAT!",
    "TIJD IS OP!"
};

const char * const TEXT_UNDO[4] = {
    "UNDO (M)",
    "DESHACER (M)",
    "DESFER (M)",
    "LOSMAKEN (M)"
};
const char * const TEXT_SOLVE[4] = {
    "SURRENDER (S)",
    "ME RINDO (S)",
    "EM RENDEIXO (S)",
    "OVERGAVE (S)"
};
    
const char * const TEXT_RESET[4] = {
    "RESET (R)",
    "RESET (R)",
    "RESET (R)",
    "RESET (R)"
};

const char * const TEXT_CONFIRM[4] = {
    "CONFIRM:",
    "CONFIRMA:",
    "CONFIRMA:",
    "BEVESTIGEN:"
};

const char * const TEXT_YES[4] = {
    "YES",
    "SI",
    "SI",
    "JA"
};

const char * const TEXT_NO[4] = {
    "NO",
    "NO",
    "NO",
    "NEE"
};

const char * const TEXT_CURRENT_RANK[4] = {
    "Current rank:",
    "Rango actual:",
    "Rang actual:",
    "Huidige rang:"
};

const char * const TEXT_PRESS_ANY_KEY[4] = {
    "Press any key",
    "Pulsa una tecla",
    "Prem una tecla",
    "Druk op iets",
};

const char * const TEXT_PROMOTION[4] = {
    "Congratulations! You got promoted!",
    "Felicidades! Has ascendido!",
    "Felicitats! Has pujat un rang!",
    "Gefeliciteerd! Je bent gepromoot!"
};

const char * const TEXT_DEMOTION[4] = {
    "Damn! You got demoted.",
    "Rayos! Has perdido un rango.",
    "Casun! Has perdut un rang.",
    "Verdomme! Je bent gedegradeerd."    
};

const char * const TEXT_ACHIEVEMENT_0[4] = {
    "Amazing! You got from ",
    "Alucinante! Has subido desde ",
    "Flipant! Has pujat desde ",
    "Verbazingwekkend! Je bent van "    
};

const char * const TEXT_ACHIEVEMENT_1[4] = {
    " to ", 
    " a ",
    " a ",    
    " naar "   
};

const char * const TEXT_ACHIEVEMENT_2[4] = {
    " in only ",  
    " en solo ",
    " en tant sols ",
    " in slechts "
};

const char * const TEXT_ACHIEVEMENT_3[4] = {
    " minutes and ",  
    " minutos y ", 
    " minuts i ", 
    " minuten en ",  
};

const char * const TEXT_ACHIEVEMENT_4[4] = {
    " seconds!",    
    " segundos!",    
    " segons!",    
    " seconden gekomen!",    
};

const char * const TEXT_SHARE[4] = {
    "share:",
    "twitea:",
    "twiteja:",
    "delen:",
};

const char * const TEXT_GOOD_ENDING[4] = {
    "You did it!\n"
    "You proved you are ready!\n"
    "Now, make America great again!",
    "Lo conseguiste!\n"
    "Has demostrado estar listo!\n"
    "Haz America grande otra vez!",
    "Ho has aconseguit!\n"
    "Has demostrat estar llest!\n"
    "Fes America grand altre vegada!",
    "Je hebt het gedaan!\n"
    "Je bent nu klaar.\n"
    "Maak Amerika weer geweldig.!"
};

const char * const TEXT_BAD_ENDING[4] = {
    "To the jail!\n The navy is not for cheaters!", 
    "A la carcel!\n La armada no es para tramposos!",
    "A la preso!\n L'armada no es per tramposos!",    
    "Gevangenis!\n De marine is niet\n voor valsspelers."   
};


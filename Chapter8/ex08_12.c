/*
 * Filename:	ex08_12.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        20/06/2017.
 * Description: LIMERICK
 */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>


void printSentence( void );
int getRandomNumber( int );


const char *twoSyllableAns[57] = {
"afghan", "batman", "bedpan", "beer can", "began", "best man",
"bhutan", "black man", "blind man", "cancan", "caveman", "cezanne",
"cheyanne", "con man", "deadpan", "declan", "diane", "divan",
"doorman", "floor plan", "frogman", "front man", "game plan", "gay man",
"ground plan", "guardsman", "hitman", "iran", "joanne", "less than",
"madman", "mailman", "milkman", "more than", "moulin", "old man",
"poor man", "rich man", "rodin", "roxanne", "saucepan", "quran",
"sideman", "snowman", "sports fan", "spray can", "straw man", "strongman",
"stunt man", "susanne", "tarzan", "tin can", "trash can", "white man",
"wild man", "wise man", "young man" };

	
const char *oneSyllableAns[16] = {
"anne", "ban", "can", "chan", "clan", "dan",		
"fan", "flan", "gran", "nan", "pan", "ran",
"span", "stan", "tan", "van"};


const char *oneSyllableSubject[30] = {
"raid", "moon", "base", "life", "head", "plot",		
"soul", "week", "door", "yard", "pole", "cord",	
"path", "step", "sack", "sword", "steel", "tongue",	
"crown", "count", "snake", "school", "boy", "girl",	
"cat", "dog", "fish", "tree", "judge", "geek"};


const char *proposition[12] = { "in", "from", "down", "of", "like", "to", 
"for", "off", "up", "at", "by", "since" };


const char *twoSyllableverbs[116] = { "added", "admired", "advised", "agreed", "allowed", "amused",
"announced", "annoyed", "answered", "appeared", "approved", "argued", 
"arranged", "arrived", "attached", "attacked", "balanced", "batted",
"behaved", "belonged", "blinded", "blotted", "boasted", "bolted",
"borrowed", "bubbled", "buried", "carried", "challenged", "cheated",
"coloured", "complained", "concerned", "confessed", "contained", "copied", 
"counted", "covered", "cycled", "damaged", "decayed", "deceived", 
"delayed", "described", "deserved", "destroyed", "disarmed", "disliked", 
"doubled", "doubted", "dusted", "earned","educated", "employed",
"enjoyed", "entered", "escaped", "excused", "explained", "faded",
"fancied", "fastened", "fitted", "floated", "flooded", "flowered",
"folded", "followed", "founded", "frightened", "gathered", "grated", 
"greeted", "guarded", "guided", "hammered", "handed", "handled", 
"happened", "harassed", "hated", "haunted", "headed", "heated", 
"hovered", "hunted", "hurried", "ignored", "impressed", "improved", 
"increased", "informed", "injured", "interfered", "juggled", "knitted", 
"knotted", "labeled", "landed", "lasted", "leveled", "licensed", 
"listed", "listened", "loaded", "emptied"};


const char *threeSyllableVerbs[50] = { "accepted", "admitted", "afforded", "alerted", "analysed", "applauded",
"arrested", "attempted", "attended", "attracted", "avoided",
"collected", "commanded", "competed", "completed", "connected", "considered", 
"consisted", "continued", "corrected", "decided", "delighted", "delivered",
"depended", "deserted", "developed", "disagreed", "disappeared", "disapproved",
"discovered", "divided", "educated", "embarrassed", "encouraged", "examined", 
"excited", "expanded", "expected", "exploded", "extended", "guaranteed",  
"influenced", "injected", "instructed", "intended", "interfered", "introduced", 
"invented", "invited" };
	

const char *oneSyllablePron[7] = { 	"he", "she", "it", "if", "when", "not",
"so" };


const char *oneSyllableLinks[12] = { 	"and", "but", "with", "for", "when", "then", 
"this", "which", "not", "like", "when", "so" };


const char *twoSyllableAdjectives[192] = {"able", "acclaimed", "aching" ,"active", "adept", "admired",
"adored", "advanced", "afraid" ,"agile", "ajar", "alarmed",
"alert", "alive", "ample" ,"amused", "anchored", "ancient",
"angry", "antique", "anxious" ,"arctic", "arid", "ashamed",
"assured", "attached", "aware" ,"awesome", "awful", "awkward",
"baggy", "basic", "beloved" ,"better", "bewitched", "bite-sized",
"bitter", "blaring", "barren" ,"blissful", "blushing", "bogus",
"boiling", "bony", "boring" ,"bossy", "bouncy", "broken",
"bulky", "bumpy", "buoyant" ,"burly", "buzzing", "candid",
"canine", "carefree", "careful" ,"careless", "caring", "cautious",
"charming", "cheerful", "cheery" ,"chilly", "chubby", "classic",
"clear-cut", "clever", "cloudy" ,"clueless", "clumsy", "cluttered",
"common", "complete", "complex" ,"composed", "concerned", "concrete",
"confused", "conscious", "constant" ,"content", "corny", "corrupt",
"costly", "crafty", "crazy" ,"creamy", "creepy", "crooked",
"crowded", "crushing", "cultured" ,"curly", "curvy", "damaged",
"dapper", "daring", "darling" ,"deadly", "dearest", "decent",
"delayed", "detailed", "dimpled" ,"direct", "discrete", "disloyal",
"dismal", "dirty", "distant" ,"distinct", "dizzy", "dopey",
"doting", "double", "downright" ,"drafty", "dreary", "droopy",
"eager", "earnest", "early" ,"empty", "enraged", "entire",
"esteemed", "expert", "failing" ,"famous", "fancy", "far-flung",
"far-off", "fatal", "fearful" ,"fearless", "feisty", "feline",
"female", "fickle", "filthy" ,"finished", "firsthand", "fitting",
"flaky", "flashy", "flawless" ,"flimsy", "flippant", "fluffy",
"focused", "foolish", "forceful" ,"formal", "fragrant", "frequent",
"friendly", "frightened", "frigid" ,"frilly", "frizzy", "frosty",
"frozen", "frugal", "fruitful" ,"fussy", "fuzzy", "gentle",
"giddy", "gifted", "giving" ,"glaring", "gleaming", "gleeful",
"gloomy", "glossy", "golden" ,"gorgeous", "graceful", "gracious",
"grateful", "greedy", "grimy" ,"gripping", "grizzled", "grouchy",
"grounded", "growing", "growling" ,"grubby", "gruesome", "grumpy" };

const char *article[7] = { "the", "that", "this", "a", "one", "some", "any"};


void printSentence()
{
	/* First line */
	printf("There once was a %s %s %s\n",
			oneSyllableSubject[getRandomNumber(30)],
			proposition[getRandomNumber(12)],
			twoSyllableAns[getRandomNumber(57)]	
	);
	
	/* Second line */
	printf("Who %s %s %s %s %s\n",
	        twoSyllableverbs[getRandomNumber(50)],
	        article[getRandomNumber(7)],
	        twoSyllableAns[getRandomNumber(57)],
	        proposition[getRandomNumber(12)],
			oneSyllableAns[getRandomNumber(16)]
	);

	/* Third line */
	const char *first = oneSyllablePron[getRandomNumber(7)];
	printf("%c%s ",toupper(first[0]), &first[1]);
	printf("%s %s\n",
	        twoSyllableAdjectives[getRandomNumber(50)], 
	        twoSyllableverbs[getRandomNumber(116)]
	);
	
	/* Fourth line */
	const char *second = oneSyllableLinks[getRandomNumber(12)];
	printf("%c%s ",toupper(second[0]), &second[1]);
	printf("%s %s\n",
	        twoSyllableAdjectives[getRandomNumber(50)], 
	        twoSyllableverbs[getRandomNumber(116)]
	);
	
	/* Fourth line */
	const char *third = oneSyllableLinks[getRandomNumber(12)];
	printf("%c%s ",toupper(third[0]), &third[1]);
	printf("%s %s %s %s\n",
	        twoSyllableAdjectives[getRandomNumber(50)], 
	        threeSyllableVerbs[getRandomNumber(50)],
	        proposition[getRandomNumber(12)],
			oneSyllableAns[getRandomNumber(16)]
	);	
	
}


/* Returns a random number in the range 0 to max-1*/
int getRandomNumber( int max )
{
	return rand()%max;
}


int main()
{	
    srand( time(NULL) );
    
    printSentence();
    
	
 	return 0;
}



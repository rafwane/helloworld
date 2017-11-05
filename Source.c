// maisie_computer_studies.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <string.h>

/* define a struct that holds all the details required of a particular paint */
struct PaintDetails {
	char  sPaintName[64];
	int   iAverageDryingTime;
	int   iNumberOfHours;
	char  sExtraDetails[1024];
	char  sCategory[64];
};

int main()
{
	/* 4 Modifying Code for Multiple Paints
	One of the common patterns of creating a program is to start with the simplest case
	and increase the complexity, one step at a time. In this case, last week, you created
	a program to handle a single paint; now, you will work on extending your code to do
	the same thing multiple times, and handle a bit more complex behaviour. A good place
	to start would be to modify your program to do the same thing 4 times (Junior drying
	inspectors have to handle at least this many paints at once).
	A bad way to implement this would be by copying the same section of code multiple
	times, as this will result in a lot of corrections if we have to change something (it also
	doesn't scale well if we want to do something thousands of times). */

	int	iInstanceOfQuestion;	/* out of the 3 questions, which one are we addressing */
	int	iAnswerGiven[3];	/* Array of integer numbers of answers given by the User */
	int	iTotalDryingTime = 0;	/* Total drying time */
	char	sArrayofDryingCategories[3];	/* Calculated Drying Categories */
											/* I = (Instant <= 1hr) ; F (Fast > 1hr && <= 2hrs) */
											/* Q = (Quick >2hrs && <= 6hrs) ; E = (Qualify failure) */
	int iInstanceOfPaint;
	const int   iNumberOfPaintsCategorised = 4; /* I will set this to 4, but it can easily be changed */

												/* this is my array of paint details */
	struct PaintDetails    pdPaintDetailsArray[4];

	for (iInstanceOfPaint = 0; iInstanceOfPaint < iNumberOfPaintsCategorised; iInstanceOfPaint++)
	{

		/* get the name of the paint */
		printf("Please enter the name of the paint\n");
		scanf("%s", pdPaintDetailsArray[iInstanceOfPaint].sPaintName);

		/* Zero time taken */
		iTotalDryingTime = 0;

		/* Ask three times for the the time to dry */
		for (iInstanceOfQuestion = 0; iInstanceOfQuestion < 3; iInstanceOfQuestion++)
		{
			/* for the user prompt, note add one to iInstanceOfQuestion as most Users count from 1 and not from zero */
			printf("For test %d enter the drying time\n", iInstanceOfQuestion + 1);
			printf("Please enter the time for the paint to dry (in minutes)\n");
			/* read the answer from the User and store it in the array of answers */
			scanf("%d", &iAnswerGiven[iInstanceOfQuestion]);
			/* add to the total */
			iTotalDryingTime = iTotalDryingTime + iAnswerGiven[iInstanceOfQuestion];

			/* Store which category the paint is in */
			int iAns = iAnswerGiven[iInstanceOfQuestion];
			if (iAns <= 60)
			{
				/* Category is Instant */
				sArrayofDryingCategories[iInstanceOfQuestion] = 'I';
			}
			else if ((iAns > 60) && (iAns <= 120))
			{
				/* Category is Fast*/
				sArrayofDryingCategories[iInstanceOfQuestion] = 'F';
			}
			else if ((iAns > 120) && (iAns <= 360))
			{
				/* Category is Quick */
				sArrayofDryingCategories[iInstanceOfQuestion] = 'Q';
			}
			else
			{
				/* None of these so the time must be > 360 minutes */
				sArrayofDryingCategories[iInstanceOfQuestion] = 'E';
			}
		} /* end of loop */

		  /* Now get the average drying time*/
		pdPaintDetailsArray[iInstanceOfPaint].iAverageDryingTime = iTotalDryingTime / 3;

		/* find out how many hours by dividing by 60 minutes*/
		pdPaintDetailsArray[iInstanceOfPaint].iNumberOfHours =
			pdPaintDetailsArray[iInstanceOfPaint].iAverageDryingTime / 60;

		/*********************/
		/* 2 Qualifying Time */
		/*********************/

		/*  In order to comply with the ‘quick drying’ regulations, a paint must dry on average strictly under 6 hours. */
		/* Add text to the output clearly indicating whether or not the paint complies. E.g. “RaceRed does not meet  */
		/* ‘quick drying’ status, with a total time of 15 hours and 43 minutes.” */


		int	iSixHoursAsMinutes = 6 * 60;
		if (pdPaintDetailsArray[iInstanceOfPaint].iAverageDryingTime < iSixHoursAsMinutes)
		{
			printf("%s qualified\n", pdPaintDetailsArray[iInstanceOfPaint].sPaintName);
		}
		else
		{
			printf("%s does not meet quick drying status and did not qualify\n", pdPaintDetailsArray[iInstanceOfPaint].sPaintName);
		}


		/* 3 Multiple Categories and Grammar */
		/* d) Paints can be separated into multiple categories that meet the different marketing regulations. In order to qualify, */
		/* all 3 patches have to dry on average within the time specified for each category. Change the output for part c) to describe */
		/* the best category the paint can be classed as, if any. */

		/* the simplest classification is where all three categories are the same */
		if ((sArrayofDryingCategories[0] == sArrayofDryingCategories[1]) &&
			(sArrayofDryingCategories[0] == sArrayofDryingCategories[2]))
		{
			/* they are all the same */
			strcpy(pdPaintDetailsArray[iInstanceOfPaint].sExtraDetails,
				"The three paint tests dried at the same time");
			if (sArrayofDryingCategories[0] == 'I')
			{
				strcpy(pdPaintDetailsArray[iInstanceOfPaint].sCategory, "Instant");
			}
			else if (sArrayofDryingCategories[0] == 'F')
			{
				strcpy(pdPaintDetailsArray[iInstanceOfPaint].sCategory, "Fast");
			}
			else if (sArrayofDryingCategories[0] == 'Q')
			{
				strcpy(pdPaintDetailsArray[iInstanceOfPaint].sCategory, "Quick");
			}
			else
			{
				strcpy(pdPaintDetailsArray[iInstanceOfPaint].sCategory, "Error");
			}

		}
		else if ((sArrayofDryingCategories[0] == 'E') ||
			(sArrayofDryingCategories[1] == 'E') ||
			(sArrayofDryingCategories[2] == 'E'))
		{

			/* if any of the drying categories was > 6 hours then the paint will be classified as a quality failure */
			/* this is not necessarily what a company would do, but I decided that this is the way I will categorise the paint */

			strcpy(pdPaintDetailsArray[iInstanceOfPaint].sCategory, "Error");
			strcpy(pdPaintDetailsArray[iInstanceOfPaint].sExtraDetails,
				"One of the tests was greater than 6 hours and fails the classification");
		}
		else
		{
			/* now we know that the times were not all the same category and that all tests were under 6 hours */
			/* find out which category occured the most frequently */
			int iCountOfInstant = 0;	/* Number of instances categorised as Instant */
			int iCountOfFast = 0;	/* Number of instances categorised as Fast*/
			int iCountOfQuick = 0;	/* Number of instances categorised as Quick */

			strcpy(pdPaintDetailsArray[iInstanceOfPaint].sExtraDetails,
				"Not all the tests completed in the same category");

			/* Loop through each answer and count how many Instants, Fasts and Quicks */
			for (iInstanceOfQuestion = 0; iInstanceOfQuestion < 3; iInstanceOfQuestion++)
			{
				if (sArrayofDryingCategories[iInstanceOfQuestion] == 'I')
				{
					/* increment the number of Instants */
					iCountOfInstant = iCountOfInstant + 1;
				}
				else if (sArrayofDryingCategories[iInstanceOfQuestion] == 'F')
				{
					/* increment the number of Fasts*/
					iCountOfFast = iCountOfFast + 1;
				}
				else if (sArrayofDryingCategories[iInstanceOfQuestion] == 'Q')
				{
					/* increment the number of Quicks */
					iCountOfQuick = iCountOfQuick + 1;
				}
			} /* end of loop */

			if ((iCountOfInstant > iCountOfFast) &&
				(iCountOfInstant > iCountOfQuick))
			{
				/* There are more Instants than Fasts or Quicks */
				strcpy(pdPaintDetailsArray[iInstanceOfPaint].sCategory, "Instant");
			}
			else if ((iCountOfFast > iCountOfInstant) &&
				(iCountOfFast  > iCountOfQuick))
			{
				/* There are more Fasts than Instants or Quicks */
				strcpy(pdPaintDetailsArray[iInstanceOfPaint].sCategory, "Fast");
			}
			else if ((iCountOfQuick  > iCountOfInstant) &&
				(iCountOfQuick  > iCountOfFast))
			{
				/* There are more Quicks than Instants or Fasts */
				strcpy(pdPaintDetailsArray[iInstanceOfPaint].sCategory, "Quick");
			}
			else
			{
				/* this is the catch all statement, where the paint could not be classified at all */
				strcpy(pdPaintDetailsArray[iInstanceOfPaint].sCategory, "Unknown");
			}
		}

	} /* end loop for number of paint */

	  /* now loop through all the paints and print out the results */
	for (iInstanceOfPaint = 0; iInstanceOfPaint < iNumberOfPaintsCategorised; iInstanceOfPaint++)
	{

		/* output the paint name and the number hours and minutes it takes to finish */
		/*printf( "pdPaintDetailsArray[iInstanceOfPaint].sPaintName = %s\n", pdPaintDetailsArray[iInstanceOfPaint].sPaintName );
		printf( "pdPaintDetailsArray[iInstanceOfPaint].iAverageDryingTime = %d\n", pdPaintDetailsArray[iInstanceOfPaint].iAverageDryingTime );
		printf( "pdPaintDetailsArray[iInstanceOfPaint].iNumberOfHours = %d\n", pdPaintDetailsArray[iInstanceOfPaint].iNumberOfHours );
		printf( "pdPaintDetailsArray[iInstanceOfPaint].sExtraDetails = %s\n", pdPaintDetailsArray[iInstanceOfPaint].sExtraDetails );
		printf( "pdPaintDetailsArray[iInstanceOfPaint].sCategory = %s\n", pdPaintDetailsArray[iInstanceOfPaint].sCategory ); */
		printf("###############\n");
		printf("Paint Number %d\n", iInstanceOfPaint + 1);
		printf("###############\n");
		printf("Paint Name: %s\n", pdPaintDetailsArray[iInstanceOfPaint].sPaintName);
		printf("Average Drying Time: %d hours and %i minutes\n",
			pdPaintDetailsArray[iInstanceOfPaint].iNumberOfHours,
			pdPaintDetailsArray[iInstanceOfPaint].iAverageDryingTime % 60);
		printf("Category: %s\n", pdPaintDetailsArray[iInstanceOfPaint].sCategory);
		printf("Extra notes: %s\n", pdPaintDetailsArray[iInstanceOfPaint].sExtraDetails);
		printf("#################################################\n");
		printf("#################################################\n");
	} /* end of loop */

	printf("Press Enter to Exit Program\n");
	getch();

	return 0;
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BSOD.js                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeniz <Discord:@teomandeniz>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:00:03 by hdeniz            #+#    #+#             */
/*   Updated: 2024/02/01 18:00:29 by hdeniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* STRING */ function
	GET_LINE()
{
	var ERROR = new Error();
	var FRAME_RE;
	var STACK;

	if (!ERROR.stack)
	{
		try
		{
			throw (ERROR);
		}
		catch (__ERROR__)
		{
			if (!ERROR.stack)
				return ("?"); // IE < 10, likely
		}
	}

	STACK = ERROR.stack.toString().split(/\r\n|\n/);
	// We want our caller's frame. It's index into |stack| depends on the
	// browser and browser version, so we need to search for the second frame:
	FRAME_RE = /:(\d+):(?:\d+)[^\d]*$/;

	do
	{
		var FRAME = STACK.shift();
	}
	while (!FRAME_RE.exec(FRAME) && STACK.length);

	return (FRAME_RE.exec(STACK.shift())[1]);
}

window.onerror = function(MESSAGE, SOURCE, LINE_NO, COLUMN_NO, ERROR)
{ // GLOBAL ERROR HANDLER FOR SYNCHRONOUS ERRORS
	BSOD(ERROR || MESSAGE, SOURCE, LINE_NO, COLUMN_NO);
	return (true); // PREVENTS DEFAULT BEHAVIOR
};

window.addEventListener('unhandledrejection', // What the fuck is this shit?!
	function(EVENT)
	{ // GLOBAL HANDLER FOR UNHANDLED PROMISE REJECTIONS...
		// IDK WTF THAT SHIT MEANS BUT ANYWAY. WHAT COULD GO WRONG? ¯\_(ツ)_/¯
		BSOD(EVENT.reason);
	}
);

const ORG_CONSOLE_ERROR = console.error; // JUST IN CASE :I

console.error = function(...ARGS) // GIVE BSOD ON console.error
{
	BSOD(ARGS);
	ORG_CONSOLE_ERROR.apply(console, ARGS);
};


function
	BSOD(ERROR, SOURCE = "???", LINE_NO = GET_LINE(), COLUMN_NO = "??")
{
	const BODY = document.getElementById("BODY");
	let MESSAGE =
		"An error has occurred. To continue:\n\n" +
		"Press Enter to retry connecting to server, or\n\n" +
		"Press CTRL+SHIFT+R to reset the caches and " +
		"re-open the website.\n" +
		"We are really sorry for this error.\n\n" +
		"Error: ";
	let PAUSE_CONTINUE = "Press any key to continue ";

	function
		EVENT_KEY(EVENT)
	{
		if (
			EVENT &&
			(
				EVENT.key !== ' ' &&
				EVENT.key !== 'Enter' &&
				EVENT.type !== "click"
			)
		)
			return ;

		document.removeEventListener("keydown", EVENT_KEY);
		window.location.reload();
	}

	SRV_STATUS_DOM = undefined;

	if (TIME_INTERVAL !== undefined)
		clearInterval(TIME_INTERVAL);

	CHANGE_FAVICON("/IMAGES/ICONS/BSOD.png");
	BODY.classList.add("BSOD");

	if (
		typeof(__LANG__) !== "undefined" &&
		typeof(__LANG__[LANG]) !== "undefined" &&
		typeof(__LANG__[LANG].BSOD) !== "undefined" &&
		__LANG__[LANG].BSOD.MESSAGE
	)
		MESSAGE = __LANG__[LANG].BSOD.MESSAGE;

	if (
		typeof(__LANG__) !== "undefined" &&
		typeof(__LANG__[LANG]) !== "undefined" &&
		typeof(__LANG__[LANG].BSOD)!== "undefined" &&
		__LANG__[LANG].BSOD.PAUSE_CONTINUE
	)
		PAUSE_CONTINUE = __LANG__[LANG].BSOD.PAUSE_CONTINUE;

	BODY.innerHTML =
		"<LINK REL='STYLESHEET' " + 
		 "HREF='https://cdn.jsdelivr.net/npm/bootstrap@" +
		 "5.3.3/dist/css/bootstrap.min.css'>" +
		"<DIV>" +
		 "<H1> GOW </H1>" +
		 "<SPAN CLASS='NORMAL'>" +
		  MESSAGE +
		   SOURCE + ":" + LINE_NO + ":" + COLUMN_NO + " - " +
		   ((ERROR && ERROR.message) || ERROR) +
		 "\n\n</SPAN>" +
		 "<SPAN CLASS='CENTER'>" +
		  PAUSE_CONTINUE +
		 "<SPAN CLASS='CMD_BLINK'>▄</SPAN></SPAN>" +
         "<DIV CLASS='mt-4'>" +
          "<BUTTON ONCLICK='window.location.reload();' " +
           "CLASS='btn-bsod'>RESET</BUTTON>" +
         "</DIV>" +
		"</DIV>";

	SET_TITLE("BSOD");

	setTimeout(
		() => {
			document.addEventListener("keydown", EVENT_KEY);
		}, 1000
	);
}

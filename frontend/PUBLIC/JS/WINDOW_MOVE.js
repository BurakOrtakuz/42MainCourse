/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WINDOW_MOVE.js                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeniz <Discord:@teomandeniz>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:00:03 by hdeniz            #+#    #+#             */
/*   Updated: 2024/02/01 18:00:29 by hdeniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

const MOUSE_EVENT =
{
	MOUSE:
	{
		X: 0,
		Y: 0
	},
	WINDOW:
	{
		X: 0,
		Y: 0,
		WIDTH: 0,
		HEIGHT: 0,
		RESIZE_ID: "",
		THIS: undefined
	}
};

function
	SET_WINDOW_POSITION(EVENT, PID) /* ONMOUSEDOWN */
{
	const PROCESS = OS.PROCESS[PID];
	const OBJECT = PROCESS && OS.PROCESS[PID].THIS;
	const RECTANGLE_SIZE = OBJECT.getBoundingClientRect();

	if (OS.PROCESS[PID].WAITING_PID !== "")
		return ;

	if (OBJECT == undefined)
	{
		BSOD({message: "SET_WINDOW_POSITION"});
		return ;
	}

	MOUSE_EVENT.WINDOW.X = RECTANGLE_SIZE.left;
	MOUSE_EVENT.WINDOW.Y = RECTANGLE_SIZE.top;
	UPDATE_WINDOW_HEADER(PID);
	MOUSE_EVENT.MOUSE.X = EVENT.clientX;
	MOUSE_EVENT.MOUSE.Y = EVENT.clientY;
	MOUSE_EVENT.WINDOW.THIS = OBJECT;
	MOUSE_EVENT.WINDOW.PID = PID;
	MOVING_OR_RESIZING_WINDOW_PID = PID;
	document.addEventListener('mousemove', MOVE_WINDOW);
}

function
	WINDOW_STOPPED_MOVING(PID) /* ONMOUSEUP */
{
	const PROCESS = OS.PROCESS[PID];
	const OBJECT = PROCESS && OS.PROCESS[PID].THIS;

	if (OBJECT == undefined)
	{
		BSOD({message: "WINDOW_STOPPED_MOVING"});
		return ;
	}

	MOUSE_EVENT.WINDOW.THIS = undefined;
	MOUSE_EVENT.WINDOW.PID = undefined;
	document.removeEventListener('mousemove', MOVE_WINDOW);
	MOVING_OR_RESIZING_WINDOW_PID = -1;

	const OBJECT_AREA = OBJECT.getBoundingClientRect();
	const X = OBJECT_AREA.left;
	const Y = OBJECT_AREA.top;
	const WIDTH = OBJECT_AREA.width;
	const HEIGHT = OBJECT_AREA.height;

	if (X < 0)
		OBJECT.style.left = "0PX";

	if (Y < 0)
		OBJECT.style.top = "0PX";

	if (X + WIDTH > window.innerWidth)
		OBJECT.style.left = (window.innerWidth - WIDTH) + "PX";

	if (Y + HEIGHT > window.innerHeight)
		OBJECT.style.top = (window.innerHeight - HEIGHT) + "PX";
}

function
	MOVE_WINDOW(EVENT) /* mousemove */
{
	if (!MOUSE_EVENT.WINDOW.THIS)
		return ;

	const SELECTION = window.getSelection();

	if (SELECTION)
		SELECTION.removeAllRanges();

	if (document.activeElement)
		document.activeElement.blur();

	if (OS.PROCESS[MOUSE_EVENT.WINDOW.PID].MAXIMIZE)
	{
		const PROCESS = OS.PROCESS[MOUSE_EVENT.WINDOW.PID];

		TITLE_BAR_DOUBLE_CLICK(MOUSE_EVENT.WINDOW.PID);
		MOUSE_EVENT.WINDOW.Y = (EVENT.clientY - 12);
		MOUSE_EVENT.WINDOW.X = (EVENT.clientX - (PROCESS.WIDTH / 2));
		PROCESS.THIS.style.top = MOUSE_EVENT.WINDOW.Y + "PX";
		PROCESS.THIS.style.left = MOUSE_EVENT.WINDOW.X + "PX";
	}

	const DELTA_X = EVENT.clientX - MOUSE_EVENT.MOUSE.X;
	const DELTA_Y = EVENT.clientY - MOUSE_EVENT.MOUSE.Y;

	MOUSE_EVENT.WINDOW.THIS.style.left =
		(MOUSE_EVENT.WINDOW.X + DELTA_X) + "PX";
	MOUSE_EVENT.WINDOW.THIS.style.top =
		(MOUSE_EVENT.WINDOW.Y + DELTA_Y) + "PX";
}

/* ************************** [v] WINDOW FIXER [v] ************************** */
var MOVING_OR_RESIZING_WINDOW_PID = -1;

document.addEventListener('mouseout',
	function (EVENT)
	{ // FOR MAKING MOVING WINDOWS NOT STUCK ON THE CURSOR
		if (MOVING_OR_RESIZING_WINDOW_PID === -1)
			return ;

		if (
			EVENT.clientY <= 0 || EVENT.clientX <= 0 ||
			(
				EVENT.clientX >= window.innerWidth ||
				EVENT.clientY >= window.innerHeight
			)
		)
		{
			WINDOW_STOPPED_MOVING(MOVING_OR_RESIZING_WINDOW_PID);
			POP_SIZE_WINDOW(MOVING_OR_RESIZING_WINDOW_PID);

			const SELECTION = window.getSelection();

			if (SELECTION)
				SELECTION.removeAllRanges();

			if (document.activeElement)
				document.activeElement.blur();

			MOVING_OR_RESIZING_WINDOW_PID = -1;
		}
	}
);
/* ************************** [^] WINDOW FIXER [^] ************************** */

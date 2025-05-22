/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DESKTOP.js                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeniz <Discord:@teomandeniz>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:00:03 by hdeniz            #+#    #+#             */
/*   Updated: 2024/02/01 18:00:29 by hdeniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

var DESKTOP = {
	APPS: document.getElementById("APPS"),
	WINDOWS: document.getElementById("WINDOWS"),
	THIS: document.getElementById("DESKTOP")
};

function
	CLICKED_ON_DESKTOP() /* ONCLICK */
{
	UPDATE_WINDOW_HEADER();
	UNFOCUS_ON_DESKTOP_ICON();
	CLOSE_START_MENU();

	if (FOCUSED_PROCESS !== undefined)
	{
		FOCUSED_PROCESS = OS.PROCESS[FOCUSED_PROCESS];
		RESET_TABS(FOCUSED_PROCESS.THIS);
		FOCUSED_PROCESS.ONBLUR();
		FOCUSED_PROCESS = undefined;
	}
}

function
	UNFOCUS_ON_DESKTOP_ICON()
{
	if (!DESKTOP || !DESKTOP.APPS)
		return ;

	DESKTOP.APPS.querySelectorAll(".APP.FOCUS").forEach(
		function (APP)
		{
			APP.classList.remove("FOCUS");
		}
	);
}

function
	FOCUS_APP(THIS) /* ONCLICK */ // FOR FOCUSING APPS ON DESKTOP
{
	CLOSE_START_MENU();
	UNFOCUS_ON_DESKTOP_ICON();
	THIS.classList.add("FOCUS");
}

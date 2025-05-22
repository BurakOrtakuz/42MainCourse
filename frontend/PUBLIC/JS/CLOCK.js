/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CLOCK.js                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeniz <Discord:@teomandeniz>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:00:03 by hdeniz            #+#    #+#             */
/*   Updated: 2024/02/01 18:00:29 by hdeniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

let TIME_INTERVAL = undefined; // FOR DELETE INTERVAL WHEN NEEDED

function
	UPDATE_CLOCK()
{
	const NOW = new Date(); // Get current time
	const HOUR = NOW.getHours().toString().padStart(2, '0');
	const MINUTE = NOW.getMinutes().toString().padStart(2, '0');
	const SECOND = NOW.getSeconds().toString().padStart(2, '0');
	const CLOCK_HOUR = document.getElementById("CLOCK_HOUR");
	const CLOCK_MINUTE = document.getElementById("CLOCK_MINUTE");
	const CLOCK_SECOND = document.getElementById("CLOCK_SECOND");

	if (CLOCK_HOUR)
		CLOCK_HOUR.innerHTML = HOUR;

	if (CLOCK_MINUTE)
		CLOCK_MINUTE.innerHTML = MINUTE;

	if (CLOCK_SECOND)
		CLOCK_SECOND.innerHTML = SECOND;
}

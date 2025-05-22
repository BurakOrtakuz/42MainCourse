/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WEB_SOCKET.js                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeniz <Discord:@teomandeniz>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:00:03 by hdeniz            #+#    #+#             */
/*   Updated: 2024/02/01 18:00:29 by hdeniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

function
	SEND_WEB_SOCKET(WEB_SOCKET, OBJECT)
{
	if (WEB_SOCKET !== undefined && WEB_SOCKET.readyState === WebSocket.OPEN)
	{
		SRV_STATUS("SOCKET");
		WEB_SOCKET.send(JSON.stringify(OBJECT));
	}
}

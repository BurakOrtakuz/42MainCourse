/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SHA256.js                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeniz <Discord:@teomandeniz>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 ??:??:?? by hdeniz            #+#    #+#             */
/*   Updated: 2024/11/01 ??:??:?? by hdeniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* STRING */ function
	SHA256(/* STRING */ VARIABLE, OPTIONS = {})
{ // Chris Veness 2002-2019 - https://www.movable-type.co.uk/scripts/sha256.html
	function
		UTF8_ENCODE(STRING)
	{
		try
		{
			return (
				new TextEncoder().encode(STRING, 'utf-8').reduce(
					(PREV, CURR) => PREV + String.fromCharCode(CURR), ''
				)
			);
		}
		catch (ERROR)
		{
			return (unescape(encodeURIComponent(STRING)));
		}
	}

	function
		HEX_BYTES_TO_STRING(HEX_STRING)
	{
		const __STRING__ = HEX_STRING.replace(' ', '');

		return (
			__STRING__ === '' ? '' :
			__STRING__.match(/.{2}/g).map(
				BYTE => String.fromCharCode(parseInt(BYTE, 16))
			).join('')
		);
	}

	function
		ROTR(N, X)
	{
		return ((X >>> N) | (X << (32 - N)));
	}

	function
		Σ0(X)
	{
		return (ROTR(2, X) ^ ROTR(13, X) ^ ROTR(22, X));
	}

	function
		Σ1(X)
	{
		return (ROTR(6, X) ^ ROTR(11, X) ^ ROTR(25, X));
	}

	function
		σ0(X)
	{
		return (ROTR(7, X) ^ ROTR(18, X) ^ (X >>> 3));
	}

	function
		σ1(X)
	{
		return (ROTR(17, X) ^ ROTR(19, X) ^ (X >>> 10));
	}

	function
		CH(X, Y, Z)
	{
		return ((X & Y) ^ (~X & Z));
	}

	function
		MAJ(X, Y, Z)
	{
		return ((X & Y) ^ (X & Z) ^ (Y & Z));
	}

	const DEFAULTS = {VARIABLE_FORMAT: 'string', OUT_FORMAT: 'hex' };
	const OPTION = { ...DEFAULTS, ...OPTIONS };
	const __K__ = [
		0X428A2F98, 0X71374491, 0XB5C0FBCF, 0XE9B5DBA5, 0X3956C25B, 0X59F111F1,
		0X923F82A4, 0XAB1C5ED5, 0XD807AA98, 0X12835B01, 0X243185BE, 0X550C7DC3,
		0X72BE5D74, 0X80DEB1FE, 0X9BDC06A7, 0XC19BF174, 0XE49B69C1, 0XEFBE4786,
		0X0FC19DC6, 0X240CA1CC, 0X2DE92C6F, 0X4A7484AA, 0X5CB0A9DC, 0X76F988DA,
		0X983E5152, 0XA831C66D, 0XB00327C8, 0XBF597FC7, 0XC6E00BF3, 0XD5A79147,
		0X06CA6351, 0X14292967, 0X27B70A85, 0X2E1B2138, 0X4D2C6DFC, 0X53380D13,
		0X650A7354, 0X766A0ABB, 0X81C2C92E, 0X92722C85, 0XA2BFE8A1, 0XA81A664B,
		0XC24B8B70, 0XC76C51A3, 0XD192E819, 0XD6990624, 0XF40E3585, 0X106AA070,
		0X19A4C116, 0X1E376C08, 0X2748774C, 0X34B0BCB5, 0X391C0CB3, 0X4ED8AA4A,
		0X5B9CCA4F, 0X682E6FF3, 0X748F82EE, 0X78A5636F, 0X84C87814, 0X8CC70208,
		0X90BEFFFA, 0XA4506CEB, 0XBEF9A3F7, 0XC67178F2
	];
	const __H__ = [
		0X6A09E667, 0XBB67AE85, 0X3C6EF372, 0XA54FF53A, 0X510E527F, 0X9B05688C,
		0X1F83D9AB, 0X5BE0CD19
	];

	if (OPTION.VARIABLE_FORMAT === 'string')
		VARIABLE = UTF8_ENCODE(VARIABLE);
	else if (OPTION.VARIABLE_FORMAT === 'hex-bytes')
		VARIABLE = HEX_BYTES_TO_STRING(VARIABLE);

	VARIABLE += String.fromCharCode(0x80);

	const N = Math.ceil((VARIABLE.length / 4 + 2) / 16);
	const M = new Array(N);
	
	for (let I = 0; I < N; I++)
	{
		M[I] = new Array(16);

		for (let J = 0; J < 16; J++)
		{
			M[I][J] =
				(VARIABLE.charCodeAt(I * 64 + J * 4 + 0) << 24) |
				(VARIABLE.charCodeAt(I * 64 + J * 4 + 1) << 16) |
				(VARIABLE.charCodeAt(I * 64 + J * 4 + 2) << 8) |
				(VARIABLE.charCodeAt(I * 64 + J * 4 + 3) << 0);
		}
	}

	const LEN_HI = ((VARIABLE.length - 1) * 8) / Math.pow(2, 32);
	const LEN_LO = ((VARIABLE.length - 1) * 8) >>> 0;

	M[N - 1][14] = Math.floor(LEN_HI);
	M[N - 1][15] = LEN_LO;

	// Hash computation
	for (let I = 0; I < N; I++) {
		const W = new Array(64);

		for (let T = 0; T < 16; T++)
			W[T] = M[I][T];

		for (let T = 16; T < 64; T++)
			W[T] = (σ1(W[T - 2]) + W[T - 7] + σ0(W[T - 15]) + W[T - 16]) >>> 0;

		let A = __H__[0];
		let B = __H__[1];
		let C = __H__[2];
		let D = __H__[3];
		let E = __H__[4];
		let F = __H__[5];
		let G = __H__[6];
		let H = __H__[7];

		for (let T = 0; T < 64; T++)
		{
			const T1 = H + Σ1(E) + CH(E, F, G) + __K__[T] + W[T];
			const T2 = Σ0(A) + MAJ(A, B, C);

			H = G;
			G = F;
			F = E;
			E = (D + T1) >>> 0;
			D = C;
			C = B;
			B = A;
			A = (T1 + T2) >>> 0;
		}

		__H__[0] = (__H__[0] + A) >>> 0;
		__H__[1] = (__H__[1] + B) >>> 0;
		__H__[2] = (__H__[2] + C) >>> 0;
		__H__[3] = (__H__[3] + D) >>> 0;
		__H__[4] = (__H__[4] + E) >>> 0;
		__H__[5] = (__H__[5] + F) >>> 0;
		__H__[6] = (__H__[6] + G) >>> 0;
		__H__[7] = (__H__[7] + H) >>> 0;
	}

	for (let H = 0; H < __H__.length; H++) // TO HEX
		__H__[H] = ('00000000' + __H__[H].toString(16)).slice(-8);

	return (__H__.join(OPTION.OUT_FORMAT === 'hex-w' ? ' ' : ''));
}

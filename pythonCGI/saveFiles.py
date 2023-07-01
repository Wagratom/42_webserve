# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    saveFiles.py                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/01 08:33:56 by wwallas-          #+#    #+#              #
#    Updated: 2023/07/01 11:17:47 by wwallas-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import io
from PIL import Image
import PyPDF2
import os

class PDFBase64File():
	ALLOWED_TYPES = ['pdf', 'jpg', 'png']

	def get_file_extension(self, filename, decoded_file):
		try:
			file = io.BytesIO(decoded_file)
			PyPDF2.PdfFileReader(file)
			return 'pdf'
		except:
			pass
		try:
			file = io.BytesIO(decoded_file)
			image = Image.open(file)
			if image.format == 'JPEG':
				return 'jpg'
			elif image.format == 'PNG':
				return 'png'
		except:
			pass
		return None

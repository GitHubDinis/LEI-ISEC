xquery version "1.0";

for $x in doc("C:/Users/Utilizador/Documents/NetBeansProjects/TrabalhoPraticoID/paises.xml")//pais
order by $x/@nome
return ('Nome: ', data($x/@nome), '&#10;')
using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace PWEB_2324.Data.Migrations
{
    public partial class populateData : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.Sql("INSERT INTO Categorias(Nome, Descricao) " +
               "VALUES('Apartamento','Categoria de Apartamentos')");

            migrationBuilder.Sql("INSERT INTO Categorias(Nome,Descricao) " +
                "VALUES('Moradia','Categoria de Moradias')");

            migrationBuilder.Sql("INSERT INTO Categorias(Nome,Descricao) " +
                "VALUES('Quarto','Categoria de Quartos')");

            migrationBuilder.Sql("INSERT INTO Categorias(Nome,Descricao) " +
               "VALUES('Garagem','Categoria de Garagem')");

            //----------------------------------------------------

            migrationBuilder.Sql("INSERT INTO Locadores(Nome,Descricao,Avaliacao) " +
              "VALUES('Remax','Remax-Porto',3)");
            migrationBuilder.Sql("INSERT INTO Locadores(Nome,Descricao,Avaliacao) " +
             "VALUES('Eximios','Eximios-Vila do Conde',5)");

            //-----------------------------------------------------

            /*migrationBuilder.Sql("INSERT INTO Imoveis(Title,Descricao,Price,Localizacao,Quartos,DataInit) " +
             "VALUES('Remax','Remax-Porto',3)");*/


        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {

        }
    }
}

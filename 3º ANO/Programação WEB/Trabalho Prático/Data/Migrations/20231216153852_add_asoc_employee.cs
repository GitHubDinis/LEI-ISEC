using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace PWEB_2324.Data.Migrations
{
    public partial class add_asoc_employee : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.AddColumn<string>(
                name: "FuncName",
                table: "Alugados",
                type: "nvarchar(max)",
                nullable: true);

            migrationBuilder.AddColumn<string>(
                name: "funcionarioId",
                table: "Alugados",
                type: "nvarchar(450)",
                nullable: true);

            migrationBuilder.CreateIndex(
                name: "IX_Alugados_funcionarioId",
                table: "Alugados",
                column: "funcionarioId");

            migrationBuilder.AddForeignKey(
                name: "FK_Alugados_Funcionarios_funcionarioId",
                table: "Alugados",
                column: "funcionarioId",
                principalTable: "Funcionarios",
                principalColumn: "Id");
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_Alugados_Funcionarios_funcionarioId",
                table: "Alugados");

            migrationBuilder.DropIndex(
                name: "IX_Alugados_funcionarioId",
                table: "Alugados");

            migrationBuilder.DropColumn(
                name: "FuncName",
                table: "Alugados");

            migrationBuilder.DropColumn(
                name: "funcionarioId",
                table: "Alugados");
        }
    }
}

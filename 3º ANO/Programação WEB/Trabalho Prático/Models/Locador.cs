using System.ComponentModel.DataAnnotations;

namespace PWEB_2324.Models
{
    public class Locador
    {
        public int Id { get; set; }

        [Display(Name = "Locador", Prompt = "Introduza o Locador!")]
        [Required(ErrorMessage = "Indique o nome do Locador!")]
        public string Nome { get; set; }

        [Display(Name = "Descrição", Prompt = "Introduza a Descrição do Locador!")]
        [Required(ErrorMessage = "Descreva o Locador!")]
        public string Descricao { get; set; }
        [Range(1, 5,
        ErrorMessage = "Avaliação de estar entre 1 e 5.")]
        public int Avaliacao { get; set; }
        public bool Ativo { get; set; } = true;
        public ICollection<Imovel> Imoveis { get; set; }
    }
}

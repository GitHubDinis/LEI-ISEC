using System.ComponentModel.DataAnnotations;

namespace PWEB_2324.Models
{
    public class Alugado
    {
        public int Id { get; set; }
        [Display(Name = "Title", Prompt = "Introduza o Título do anuncio!")]
        [Required(ErrorMessage = "Indique o título do anuncio!")]
        public string Title { get; set; }

        [Display(Name = "Descrição", Prompt = "Introduza a Descrição do imovel!")]
        [Required(ErrorMessage = "Descreva o imovel!")]
        public string Descricao { get; set; }
        [Range(1, 5,
        ErrorMessage = "Avaliação de estar entre 1 e 5.")]
        public int Avaliacao { get; set; }
        [Display(Name = "DataInit", Prompt = "Introduza a data inicial para entrar!")]
        [Required(ErrorMessage = "Indique a data inicial para entrar!")]
        public DateTime DataInit { get; set; }
        [Display(Name = "DataEnd", Prompt = "Introduza a data de saida!")]
        [Required(ErrorMessage = "Indique a data de saida!")]
        public DateTime DataEnd { get; set; }
        [Display(Name = "TempoMin", Prompt = "Introduza o tempo minimo em meses!")]
        [Required(ErrorMessage = "Indique o tempo minimo em meses!")]
        public int TempoMin { get; set; }
        public int State {  get; set; }
        public string? ClienteId { get; set; }
        public Cliente cliente { get; set; }
        public int ImovelId { get; set; }
        public Imovel imovel { get; set; }
        public int LocadorId { get; set; }
        public Locador locador { get; set; }
        public string? FuncName { get; set; }
        public Employee funcionario { get; set; }

        public Alugado() { }
        public Alugado(string Title, string Descricao, string ClienteId, int ImovelId, DateTime DataInit, DateTime DataEnd, int TempoMin, int LocadorId)
        {
            this.Title = Title;
            this.Descricao = Descricao;
            this.Avaliacao = 0;
            this.ClienteId = ClienteId;
            this.ImovelId = ImovelId;
            this.DataInit = DataInit;
            this.DataEnd = DataEnd;
            this.TempoMin = TempoMin;
            this.State = 0;
            this.LocadorId = LocadorId;

        }
    }
   
}

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Database;
using Microsoft.EntityFrameworkCore;

namespace EFCore_getting_started_mdocs
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private readonly BloggingContext _context;
        private CollectionViewSource blogViewSource;

        public MainWindow()
        {
            InitializeComponent();

            _context = new BloggingContext();
            blogViewSource = (CollectionViewSource)FindResource(nameof(blogViewSource));
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            _context.Blogs.Load();
            blogViewSource.Source = _context.Blogs.Local
                .ToObservableCollection();
        }

        private void buttonSave_Click(object sender, RoutedEventArgs e)
        {
            _context.SaveChanges();

            blogDataGrid.Items.Refresh();
            postDataGrid.Items.Refresh();
        }


        protected override void OnClosing(CancelEventArgs e)
        {
            _context.Dispose();
            base.OnClosing(e);
        }
    }
}
